import { CanvasTexture, SRGBColorSpace } from 'three'

function hashString(str: string): number {
  let h = 0
  for (let i = 0; i < str.length; i++) {
    h = (h * 31 + str.charCodeAt(i)) | 0
  }
  return Math.abs(h)
}

function seededRandom(seed: number) {
  let t = seed
  return () => {
    t += 0x6d2b79f5
    let r = Math.imul(t ^ (t >>> 15), 1 | t)
    r = (r + Math.imul(r ^ (r >>> 7), 61 | r)) ^ r
    return ((r ^ (r >>> 14)) >>> 0) / 4294967296
  }
}

function hexToRgb(hex: string): [number, number, number] {
  const num = parseInt(hex.replace('#', ''), 16)
  return [(num >> 16) & 255, (num >> 8) & 255, num & 255]
}

function rgbToHex(r: number, g: number, b: number) {
  const c = (v: number) => Math.max(0, Math.min(255, Math.round(v)))
    .toString(16)
    .padStart(2, '0')
  return `#${c(r)}${c(g)}${c(b)}`
}

/** Éclaircit (percent > 0) ou assombrit (percent < 0) une couleur hex. */
function shade(hex: string, percent: number) {
  const [r, g, b] = hexToRgb(hex)
  const target = percent < 0 ? 0 : 255
  const p = Math.abs(percent) / 100
  return rgbToHex(r + (target - r) * p, g + (target - g) * p, b + (target - b) * p)
}

/** Fait pivoter la teinte pour obtenir une couleur d'accent harmonieuse (pas un simple opposé). */
function accentColor(hex: string) {
  const [r, g, b] = hexToRgb(hex).map((v) => v / 255)
  const max = Math.max(r, g, b)
  const min = Math.min(r, g, b)
  let h = 0
  const l = (max + min) / 2
  const d = max - min
  const s = d === 0 ? 0 : l > 0.5 ? d / (2 - max - min) : d / (max + min)
  if (d !== 0) {
    switch (max) {
      case r:
        h = (g - b) / d + (g < b ? 6 : 0)
        break
      case g:
        h = (b - r) / d + 2
        break
      default:
        h = (r - g) / d + 4
    }
    h /= 6
  }
  h = (h + 150 / 360) % 1

  const hue2rgb = (p: number, q: number, t: number) => {
    if (t < 0) t += 1
    if (t > 1) t -= 1
    if (t < 1 / 6) return p + (q - p) * 6 * t
    if (t < 1 / 2) return q
    if (t < 2 / 3) return p + (q - p) * (2 / 3 - t) * 6
    return p
  }
  let r2 = l
  let g2 = l
  let b2 = l
  if (s !== 0) {
    const q = l < 0.5 ? l * (1 + s) : l + s - l * s
    const p = 2 * l - q
    r2 = hue2rgb(p, q, h + 1 / 3)
    g2 = hue2rgb(p, q, h)
    b2 = hue2rgb(p, q, h - 1 / 3)
  }
  return rgbToHex(r2 * 255, g2 * 255, b2 * 255)
}

const INK = '#171016'

/** Lettrage façon logo de couverture BD : contour encré épais + aplat clair par-dessus. */
function strokeFillText(
  ctx: CanvasRenderingContext2D,
  text: string,
  x: number,
  y: number,
  fill: string,
  strokeWidth: number,
) {
  ctx.lineJoin = 'round'
  ctx.miterLimit = 2
  ctx.strokeStyle = INK
  ctx.lineWidth = strokeWidth
  ctx.strokeText(text, x, y)
  ctx.fillStyle = fill
  ctx.fillText(text, x, y)
}

function fitFontSize(
  ctx: CanvasRenderingContext2D,
  text: string,
  fontAt: (size: number) => string,
  startSize: number,
  maxWidth: number,
) {
  let size = startSize
  ctx.font = fontAt(size)
  const measured = ctx.measureText(text).width
  if (measured > maxWidth) {
    size = Math.max(12, Math.floor((size * maxWidth) / measured))
    ctx.font = fontAt(size)
  }
  return size
}

const TITLE_FONT = (size: number) => `900 ${size}px "Arial Black", Impact, sans-serif`
const SERIF_FONT = (size: number, italic = false) =>
  `${italic ? 'italic ' : ''}${size}px "Georgia", serif`

/** Aplat de silhouette "ligne claire" : couleur pleine + contour encré épais. */
function flatShape(
  ctx: CanvasRenderingContext2D,
  points: [number, number][],
  fill: string,
  outline = 7,
) {
  ctx.beginPath()
  ctx.moveTo(points[0][0], points[0][1])
  for (let i = 1; i < points.length; i++) ctx.lineTo(points[i][0], points[i][1])
  ctx.closePath()
  ctx.fillStyle = fill
  ctx.fill()
  ctx.lineJoin = 'round'
  ctx.strokeStyle = INK
  ctx.lineWidth = outline
  ctx.stroke()
}

function flatCircle(
  ctx: CanvasRenderingContext2D,
  cx: number,
  cy: number,
  r: number,
  fill: string,
  outline = 7,
) {
  ctx.beginPath()
  ctx.arc(cx, cy, r, 0, Math.PI * 2)
  ctx.fillStyle = fill
  ctx.fill()
  ctx.strokeStyle = INK
  ctx.lineWidth = outline
  ctx.stroke()
}

type SceneParams = {
  w: number
  h: number
  horizon: number
  color: string
  accent: string
  rand: () => number
}

const SCENE_TEMPLATES: Array<(ctx: CanvasRenderingContext2D, p: SceneParams) => void> = [
  // montagnes
  function mountains(ctx, { w, h, horizon, color, accent, rand }) {
    flatCircle(ctx, w * (0.28 + rand() * 0.4), horizon - h * 0.16, 68, shade(accent, 20))
    flatShape(
      ctx,
      [
        [-10, horizon + h * 0.1],
        [w * 0.26, horizon - h * 0.12],
        [w * 0.5, horizon + h * 0.02],
        [w * 0.72, horizon - h * 0.16],
        [w + 10, horizon + h * 0.06],
        [w + 10, horizon + h * 0.28],
        [-10, horizon + h * 0.28],
      ],
      shade(color, -28),
    )
    flatShape(
      ctx,
      [
        [-10, horizon + h * 0.24],
        [w * 0.16, horizon + h * 0.08],
        [w * 0.4, horizon + h * 0.26],
        [w * 0.66, horizon + h * 0.04],
        [w + 10, horizon + h * 0.26],
        [w + 10, h + 10],
        [-10, h + 10],
      ],
      shade(color, -46),
    )
  },
  // vagues / mer
  function waves(ctx, { w, h, horizon, color, accent, rand }) {
    flatCircle(ctx, w * (0.66 + rand() * 0.15), horizon - h * 0.14, 58, shade(accent, 22))
    const waveLayer = (yBase: number, amp: number, fill: string) => {
      const pts: [number, number][] = [[-10, h + 10], [-10, yBase]]
      const steps = 7
      for (let i = 0; i <= steps; i++) {
        const x = (w / steps) * i
        const y = yBase + Math.sin(i * 1.4 + rand() * 2) * amp
        pts.push([x, y])
      }
      pts.push([w + 10, h + 10])
      flatShape(ctx, pts, fill)
    }
    waveLayer(horizon + h * 0.06, 14, shade(color, -22))
    waveLayer(horizon + h * 0.2, 16, shade(color, -42))
  },
  // toits de ville
  function skyline(ctx, { w, h, horizon, color, accent, rand }) {
    flatCircle(ctx, w * 0.78, horizon - h * 0.18, 46, shade(accent, 26))
    const drawRow = (baseY: number, fill: string, count: number) => {
      let x = -10
      for (let i = 0; i < count; i++) {
        const bw = w / count + rand() * 14 - 7
        const bh = h * (0.14 + rand() * 0.22)
        flatShape(
          ctx,
          [
            [x, baseY],
            [x + bw, baseY],
            [x + bw, baseY - bh],
            [x, baseY - bh],
          ],
          fill,
          6,
        )
        x += bw
      }
    }
    drawRow(horizon + h * 0.3, shade(color, -46), 5)
    drawRow(horizon + h * 0.32, shade(color, -26), 7)
  },
  // forêt de sapins
  function forest(ctx, { w, h, horizon, color, accent, rand }) {
    flatCircle(ctx, w * 0.24, horizon - h * 0.2, 50, shade(accent, 24))
    const row = (baseY: number, fill: string, count: number, scale: number) => {
      const step = w / count
      for (let i = 0; i < count; i++) {
        const cx = step * i + step / 2 + (rand() - 0.5) * step * 0.3
        const th = h * 0.22 * scale
        const tw = step * 0.55
        flatShape(
          ctx,
          [
            [cx, baseY - th],
            [cx + tw / 2, baseY],
            [cx - tw / 2, baseY],
          ],
          fill,
          6,
        )
      }
    }
    row(horizon + h * 0.14, shade(color, -22), 6, 0.85)
    row(horizon + h * 0.3, shade(color, -44), 8, 1.1)
  },
  // dunes du désert
  function desert(ctx, { w, h, horizon, color, accent, rand }) {
    flatCircle(ctx, w * (0.3 + rand() * 0.3), horizon - h * 0.12, 72, shade(accent, 18))
    const dune = (yBase: number, amp: number, fill: string) => {
      const pts: [number, number][] = [[-10, h + 10], [-10, yBase]]
      const steps = 5
      for (let i = 0; i <= steps; i++) {
        const x = (w / steps) * i
        const y = yBase - Math.sin((i / steps) * Math.PI) * amp
        pts.push([x, y])
      }
      pts.push([w + 10, h + 10])
      flatShape(ctx, pts, fill)
    }
    dune(horizon + h * 0.14, h * 0.06, shade(color, -18))
    dune(horizon + h * 0.28, h * 0.08, shade(color, -38))
  },
]

function paperGrain(ctx: CanvasRenderingContext2D, w: number, h: number, seed: number, amount = 0.05) {
  const rand = seededRandom(seed)
  ctx.save()
  ctx.globalAlpha = amount
  for (let i = 0; i < 260; i++) {
    ctx.fillStyle = rand() > 0.5 ? '#ffffff' : '#000000'
    ctx.fillRect(rand() * w, rand() * h, 1.2, 1.2)
  }
  ctx.restore()
}

function edgeWear(ctx: CanvasRenderingContext2D, w: number, h: number) {
  const grad = ctx.createRadialGradient(w / 2, h / 2, h * 0.35, w / 2, h / 2, h * 0.72)
  grad.addColorStop(0, 'rgba(0,0,0,0)')
  grad.addColorStop(1, 'rgba(0,0,0,0.22)')
  ctx.fillStyle = grad
  ctx.fillRect(0, 0, w, h)
}

function tomeNumber(title: string) {
  return 1 + (hashString(title) % 9)
}

function makeTexture(canvas: HTMLCanvasElement) {
  const texture = new CanvasTexture(canvas)
  texture.colorSpace = SRGBColorSpace
  texture.anisotropy = 4
  texture.needsUpdate = true
  return texture
}

/** Texture de tranche : fond en aplat, bandeaux encrés, lettrage outlined façon reliure BD. */
export function createSpineTexture(color: string, title: string) {
  const canvas = document.createElement('canvas')
  canvas.width = 128
  canvas.height = 512
  const ctx = canvas.getContext('2d')!
  const w = canvas.width
  const h = canvas.height

  ctx.fillStyle = shade(color, -4)
  ctx.fillRect(0, 0, w, h)

  const bandColor = shade(color, -50)
  ctx.fillStyle = bandColor
  ctx.fillRect(0, 0, w, 26)
  ctx.fillRect(0, h - 26, w, 26)
  ctx.fillStyle = 'rgba(255,255,255,0.85)'
  ctx.fillRect(0, 30, w, 3)
  ctx.fillRect(0, h - 34, w, 3)

  const accent = accentColor(color)
  ctx.fillStyle = shade(accent, 15)
  ctx.beginPath()
  ctx.arc(w / 2, h - 15, 7, 0, Math.PI * 2)
  ctx.fill()
  ctx.fillStyle = '#fff'
  ctx.font = 'bold 11px Georgia, serif'
  ctx.textAlign = 'center'
  ctx.textBaseline = 'middle'
  ctx.fillText(String(tomeNumber(title)), w / 2, h - 15)

  ctx.save()
  ctx.translate(w / 2, h / 2)
  ctx.rotate(Math.PI / 2)
  ctx.textAlign = 'center'
  ctx.textBaseline = 'middle'
  const size = fitFontSize(ctx, title, TITLE_FONT, 46, h - 100)
  ctx.font = TITLE_FONT(size)
  strokeFillText(ctx, title, 0, 2, '#f7f5ee', 5)
  ctx.restore()

  paperGrain(ctx, w, h, hashString(title))

  return makeTexture(canvas)
}

/** Couverture façon "ligne claire" : aplats francs, contour encré, lettrage logo, plaquette tome. */
export function createCoverTexture(color: string, title: string, author: string) {
  const canvas = document.createElement('canvas')
  canvas.width = 512
  canvas.height = 720
  const ctx = canvas.getContext('2d')!
  const w = canvas.width
  const h = canvas.height
  const rand = seededRandom(hashString(title + color))
  const accent = accentColor(color)

  // ciel en aplat (pas de dégradé : signature ligne claire)
  ctx.fillStyle = shade(color, 26)
  ctx.fillRect(0, 0, w, h)

  const template = SCENE_TEMPLATES[hashString(title) % SCENE_TEMPLATES.length]
  template(ctx, { w, h, horizon: h * 0.6, color, accent, rand })

  // cadre album : double filet encré
  ctx.strokeStyle = INK
  ctx.lineWidth = 10
  ctx.strokeRect(14, 14, w - 28, h - 28)
  ctx.strokeStyle = 'rgba(255,255,255,0.9)'
  ctx.lineWidth = 3
  ctx.strokeRect(24, 24, w - 48, h - 48)

  // bandeau-titre
  const bannerH = 122
  const bannerY = 52
  flatShape(
    ctx,
    [
      [44, bannerY],
      [w - 44, bannerY],
      [w - 44, bannerY + bannerH],
      [44, bannerY + bannerH],
    ],
    shade(color, -55),
    8,
  )
  ctx.fillStyle = '#f7f5ee'
  ctx.textAlign = 'center'
  ctx.textBaseline = 'middle'
  const titleSize = fitFontSize(ctx, title, TITLE_FONT, 58, w - 130)
  ctx.font = TITLE_FONT(titleSize)
  strokeFillText(ctx, title, w / 2, bannerY + bannerH / 2 + 2, '#f7f5ee', 7)

  // plaquette "tome"
  const badgeX = w - 78
  const badgeY = bannerY + bannerH + 56
  flatCircle(ctx, badgeX, badgeY, 34, shade(accent, 10), 6)
  ctx.fillStyle = '#fff'
  ctx.font = 'bold 26px Georgia, serif'
  ctx.textAlign = 'center'
  ctx.textBaseline = 'middle'
  ctx.fillText(`T.${tomeNumber(title)}`, badgeX, badgeY + 1)

  // signature auteur
  ctx.fillStyle = 'rgba(255,255,255,0.92)'
  ctx.font = 'italic 26px Georgia, serif'
  ctx.textAlign = 'center'
  ctx.shadowColor = 'rgba(0,0,0,0.4)'
  ctx.shadowBlur = 6
  ctx.fillText(author, w / 2, h - 88)
  ctx.shadowBlur = 0

  ctx.fillStyle = 'rgba(255,255,255,0.7)'
  ctx.font = '20px "Georgia", serif'
  ctx.fillText('Collection BdTidy', w / 2, h - 54)

  paperGrain(ctx, w, h, hashString(title + color))
  edgeWear(ctx, w, h)

  return makeTexture(canvas)
}

/** Page de titre intérieure (papier crème + titre + auteur), révélée quand la couverture s'ouvre. */
export function createTitlePageTexture(color: string, title: string, author: string) {
  const canvas = document.createElement('canvas')
  canvas.width = 512
  canvas.height = 720
  const ctx = canvas.getContext('2d')!
  const w = canvas.width
  const h = canvas.height

  ctx.fillStyle = PAPER_COLOR
  ctx.fillRect(0, 0, w, h)

  const spineShadow = ctx.createLinearGradient(0, 0, w * 0.18, 0)
  spineShadow.addColorStop(0, 'rgba(0,0,0,0.14)')
  spineShadow.addColorStop(1, 'rgba(0,0,0,0)')
  ctx.fillStyle = spineShadow
  ctx.fillRect(0, 0, w * 0.18, h)

  ctx.strokeStyle = shade(color, -10)
  ctx.lineWidth = 2
  ctx.strokeRect(w * 0.14, h * 0.28, w * 0.72, 3)
  ctx.strokeRect(w * 0.14, h * 0.4, w * 0.72, 3)

  ctx.fillStyle = shade(color, -35)
  ctx.textAlign = 'center'
  ctx.textBaseline = 'middle'
  const titleSize = fitFontSize(ctx, title, TITLE_FONT, 42, w * 0.7)
  ctx.font = TITLE_FONT(titleSize)
  ctx.lineJoin = 'round'
  ctx.strokeStyle = shade(color, -10)
  ctx.lineWidth = 1.5
  ctx.strokeText(title, w / 2, h * 0.34)
  ctx.fillText(title, w / 2, h * 0.34)

  ctx.font = SERIF_FONT(24, true)
  ctx.fillStyle = shade(color, -20)
  ctx.fillText(author, w / 2, h * 0.45)

  ctx.font = SERIF_FONT(19)
  ctx.fillStyle = shade(color, -12)
  ctx.fillText('Collection BdTidy', w / 2, h * 0.51)

  paperGrain(ctx, w, h, hashString(title + author), 0.03)

  return makeTexture(canvas)
}

/** Couleur "papier" chaude pour les tranches de pages / bords non illustrés. */
export const PAPER_COLOR = '#efe6d3'
export { shade }
