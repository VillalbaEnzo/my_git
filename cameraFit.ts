/** Distance caméra nécessaire pour que targetWidth x targetHeight tienne entièrement dans le cadre. */
export function fitDistance(
  targetWidth: number,
  targetHeight: number,
  fovDeg: number,
  aspect: number,
) {
  const vFov = (fovDeg * Math.PI) / 180
  const distForHeight = targetHeight / (2 * Math.tan(vFov / 2))
  const distForWidth = targetWidth / (2 * Math.tan(vFov / 2) * aspect)
  return Math.max(distForHeight, distForWidth)
}

/** Hauteur visible par la caméra à une distance donnée (frustum vertical). */
export function visibleHeightAt(distance: number, fovDeg: number) {
  const vFov = (fovDeg * Math.PI) / 180
  return 2 * distance * Math.tan(vFov / 2)
}
