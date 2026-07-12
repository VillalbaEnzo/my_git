from __future__ import annotations

import cv2
import numpy as np

from app.core.config import settings
from app.models.schemas import ImageQualityReport


class ImageProcessor:
    def __init__(self) -> None:
        self.max_dimension = settings.max_image_dimension

    def process(self, image_bytes: bytes) -> tuple[bytes, ImageQualityReport]:
        warnings: list[str] = []

        image = self._decode(image_bytes)
        if image is None:
            report = ImageQualityReport(
                sharpness_score=0.0,
                brightness_score=0.0,
                quality_score=0.0,
                warnings=["Image illisible ou format non supporté"],
            )
            return image_bytes, report

        image = self._resize_if_needed(image)

        was_cropped = False
        cropped = self._auto_crop_document(image)
        if cropped is not None:
            image = cropped
            was_cropped = True

        was_deskewed = False
        deskewed = self._deskew(image)
        if deskewed is not None:
            image = deskewed
            was_deskewed = True

        image = self._enhance_contrast(image)
        image = self._denoise(image)

        sharpness = self._compute_sharpness(image)
        brightness = self._compute_brightness(image)

        if sharpness < 50:
            warnings.append("Image floue : la netteté est faible")
        if brightness < 60 or brightness > 200:
            warnings.append("Éclairage sous-optimal (trop sombre ou surexposé)")

        quality_score = self._compute_quality_score(sharpness, brightness)

        success, buffer = cv2.imencode(".jpg", image, [cv2.IMWRITE_JPEG_QUALITY, 95])
        output_bytes = buffer.tobytes() if success else image_bytes

        report = ImageQualityReport(
            sharpness_score=round(sharpness, 2),
            brightness_score=round(brightness, 2),
            quality_score=round(quality_score, 3),
            was_deskewed=was_deskewed,
            was_cropped=was_cropped,
            warnings=warnings,
        )
        return output_bytes, report

    @staticmethod
    def _decode(image_bytes: bytes) -> np.ndarray | None:
        arr = np.frombuffer(image_bytes, dtype=np.uint8)
        image = cv2.imdecode(arr, cv2.IMREAD_COLOR)
        return image

    def _resize_if_needed(self, image: np.ndarray) -> np.ndarray:
        h, w = image.shape[:2]
        largest = max(h, w)
        if largest <= self.max_dimension:
            return image
        scale = self.max_dimension / largest
        return cv2.resize(image, (int(w * scale), int(h * scale)), interpolation=cv2.INTER_AREA)

    @staticmethod
    def _auto_crop_document(image: np.ndarray) -> np.ndarray | None:
        gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
        blurred = cv2.GaussianBlur(gray, (5, 5), 0)
        edges = cv2.Canny(blurred, 50, 150)
        edges = cv2.dilate(edges, np.ones((5, 5), np.uint8), iterations=1)

        contours, _ = cv2.findContours(edges, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
        if not contours:
            return None

        image_area = image.shape[0] * image.shape[1]
        largest = max(contours, key=cv2.contourArea)

        if cv2.contourArea(largest) < 0.2 * image_area:
            return None

        x, y, w, h = cv2.boundingRect(largest)
        pad = int(0.01 * max(w, h))
        x0, y0 = max(0, x - pad), max(0, y - pad)
        x1 = min(image.shape[1], x + w + pad)
        y1 = min(image.shape[0], y + h + pad)
        cropped = image[y0:y1, x0:x1]

        if cropped.size == 0:
            return None
        return cropped

    @staticmethod
    def _deskew(image: np.ndarray) -> np.ndarray | None:
        gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
        _, thresh = cv2.threshold(gray, 0, 255, cv2.THRESH_BINARY_INV + cv2.THRESH_OTSU)
        coords = cv2.findNonZero(thresh)
        if coords is None:
            return None

        angle = cv2.minAreaRect(coords)[-1]
        if angle < -45:
            angle = -(90 + angle)
        else:
            angle = -angle

        if abs(angle) < 0.5 or abs(angle) > 20:
            return None

        (h, w) = image.shape[:2]
        center = (w // 2, h // 2)
        matrix = cv2.getRotationMatrix2D(center, angle, 1.0)
        rotated = cv2.warpAffine(
            image, matrix, (w, h), flags=cv2.INTER_CUBIC, borderMode=cv2.BORDER_REPLICATE
        )
        return rotated

    @staticmethod
    def _enhance_contrast(image: np.ndarray) -> np.ndarray:
        lab = cv2.cvtColor(image, cv2.COLOR_BGR2LAB)
        l_channel, a_channel, b_channel = cv2.split(lab)
        clahe = cv2.createCLAHE(clipLimit=2.0, tileGridSize=(8, 8))
        l_channel = clahe.apply(l_channel)
        merged = cv2.merge((l_channel, a_channel, b_channel))
        return cv2.cvtColor(merged, cv2.COLOR_LAB2BGR)

    @staticmethod
    def _denoise(image: np.ndarray) -> np.ndarray:
        return cv2.fastNlMeansDenoisingColored(image, None, h=5, hColor=5, templateWindowSize=7, searchWindowSize=21)

    @staticmethod
    def _compute_sharpness(image: np.ndarray) -> float:
        gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
        return float(cv2.Laplacian(gray, cv2.CV_64F).var())

    @staticmethod
    def _compute_brightness(image: np.ndarray) -> float:
        gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
        return float(np.mean(gray))

    @staticmethod
    def _compute_quality_score(sharpness: float, brightness: float) -> float:
        sharpness_norm = min(sharpness / 150.0, 1.0)
        brightness_norm = 1.0 - min(abs(brightness - 130.0) / 130.0, 1.0)
        return max(0.0, min(1.0, 0.6 * sharpness_norm + 0.4 * brightness_norm))


image_processor = ImageProcessor()
