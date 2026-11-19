import { CanvasTexture, RepeatWrapping, SRGBColorSpace } from 'three'

function seededRandom(seed: number) {
  let t = seed
  return () => {
    t += 0x6d2b79f5
    let r = Math.imul(t ^ (t >>> 15), 1 | t)
    r = (r + Math.imul(r ^ (r >>> 7), 61 | r)) ^ r
    return ((r ^ (r >>> 14)) >>> 0) / 4294967296
  }
}

function makeRepeatingTexture(canvas: HTMLCanvasElement, repeatX: number, repeatY: number) {
  const texture = new CanvasTexture(canvas)
  texture.colorSpace = SRGBColorSpace
  texture.wrapS = RepeatWrapping
  texture.wrapT = RepeatWrapping
  texture.repeat.set(repeatX, repeatY)
  texture.anisotropy = 4
  texture.needsUpdate = true
  return texture
}

/**
 * Planches de bois horizontales, chaleureuses, avec veinage et nœuds.
 * `tone` décale la teinte de base (murs plus clairs, sol plus foncé...).
 */
export function createPlankTexture(seed: number, base = '#8a5f3c', repeatX = 2, repeatY = 2) {
  const canvas = document.createElement('canvas')
  canvas.width = 512
  canvas.height = 512
  const ctx = canvas.getContext('2d')!
  const w = canvas.width
  const h = canvas.height
  const rand = seededRandom(seed)

  ctx.fillStyle = base
  ctx.fillRect(0, 0, w, h)

  const plankCount = 6
  const plankH = h / plankCount

  for (let p = 0; p < plankCount; p++) {
    const y = p * plankH
    const lightness = (rand() - 0.5) * 26

    ctx.fillStyle = `rgba(${lightness > 0 ? '255,235,205' : '40,20,8'},${Math.abs(lightness) / 100})`
    ctx.fillRect(0, y, w, plankH)

    // veinage : lignes ondulées translucides
    const grainCount = 7 + Math.floor(rand() * 5)
    for (let g = 0; g < grainCount; g++) {
      const gy = y + rand() * plankH
      ctx.beginPath()
      ctx.moveTo(0, gy)
      for (let x = 0; x <= w; x += 32) {
        ctx.lineTo(x, gy + Math.sin(x * 0.02 + rand() * 6) * 2.5)
      }
      ctx.strokeStyle = `rgba(35,18,6,${0.08 + rand() * 0.1})`
      ctx.lineWidth = 0.8 + rand() * 1.4
      ctx.stroke()
    }

    // nœuds occasionnels
    if (rand() > 0.55) {
      const kx = rand() * w
      const ky = y + plankH * (0.3 + rand() * 0.4)
      const kr = 4 + rand() * 7
      for (let ring = 3; ring >= 1; ring--) {
        ctx.beginPath()
        ctx.ellipse(kx, ky, kr * ring * 0.5, kr * ring * 0.34, 0, 0, Math.PI * 2)
        ctx.strokeStyle = `rgba(30,15,5,${0.28 - ring * 0.06})`
        ctx.lineWidth = 1.2
        ctx.stroke()
      }
      ctx.beginPath()
      ctx.ellipse(kx, ky, 2.2, 1.6, 0, 0, Math.PI * 2)
      ctx.fillStyle = 'rgba(28,14,5,0.55)'
      ctx.fill()
    }

    // rainure entre planches
    ctx.fillStyle = 'rgba(20,10,4,0.5)'
    ctx.fillRect(0, y + plankH - 2, w, 2)
    ctx.fillStyle = 'rgba(255,240,220,0.08)'
    ctx.fillRect(0, y, w, 1.5)
  }

  return makeRepeatingTexture(canvas, repeatX, repeatY)
}

/** Tapis tissé : fond chaud, motif de losanges façon kilim, bordure. */
export function createRugTexture(seed = 41) {
  const canvas = document.createElement('canvas')
  canvas.width = 512
  canvas.height = 340
  const ctx = canvas.getContext('2d')!
  const w = canvas.width
  const h = canvas.height
  const rand = seededRandom(seed)

  ctx.fillStyle = '#7d3b30'
  ctx.fillRect(0, 0, w, h)

  // trame tissée : fines lignes horizontales
  for (let y = 0; y < h; y += 3) {
    ctx.fillStyle = `rgba(0,0,0,${0.04 + (y % 6 === 0 ? 0.05 : 0)})`
    ctx.fillRect(0, y, w, 1)
  }

  // bordures
  ctx.fillStyle = '#5c2a22'
  ctx.fillRect(0, 0, w, 26)
  ctx.fillRect(0, h - 26, w, 26)
  ctx.fillRect(0, 0, 26, h)
  ctx.fillRect(w - 26, 0, 26, h)
  ctx.strokeStyle = '#d9b380'
  ctx.lineWidth = 3
  ctx.strokeRect(34, 34, w - 68, h - 68)

  // losanges kilim
  const cols = 5
  const rows = 3
  const cellW = (w - 100) / cols
  const cellH = (h - 100) / rows
  const palette = ['#d9b380', '#a34e3d', '#e0c9a6', '#8a5f3c']
  for (let r = 0; r < rows; r++) {
    for (let c = 0; c < cols; c++) {
      const cx = 50 + c * cellW + cellW / 2
      const cy = 50 + r * cellH + cellH / 2
      const dw = cellW * 0.34
      const dh = cellH * 0.36
      ctx.beginPath()
      ctx.moveTo(cx, cy - dh)
      ctx.lineTo(cx + dw, cy)
      ctx.lineTo(cx, cy + dh)
      ctx.lineTo(cx - dw, cy)
      ctx.closePath()
      ctx.fillStyle = palette[(r + c) % palette.length]
      ctx.fill()
      ctx.beginPath()
      ctx.moveTo(cx, cy - dh * 0.45)
      ctx.lineTo(cx + dw * 0.45, cy)
      ctx.lineTo(cx, cy + dh * 0.45)
      ctx.lineTo(cx - dw * 0.45, cy)
      ctx.closePath()
      ctx.fillStyle = '#5c2a22'
      ctx.fill()
    }
  }

  // usure
  for (let i = 0; i < 500; i++) {
    ctx.fillStyle = `rgba(255,240,220,${rand() * 0.05})`
    ctx.fillRect(rand() * w, rand() * h, 1.5, 1.5)
  }

  return makeRepeatingTexture(canvas, 1, 1)
}

/** Pierre de cheminée : moellons irréguliers gris chauds avec joints sombres. */
export function createStoneTexture(seed = 77) {
  const canvas = document.createElement('canvas')
  canvas.width = 512
  canvas.height = 512
  const ctx = canvas.getContext('2d')!
  const w = canvas.width
  const h = canvas.height
  const rand = seededRandom(seed)

  ctx.fillStyle = '#4a4038'
  ctx.fillRect(0, 0, w, h)

  const rows = 7
  const stoneH = h / rows
  for (let r = 0; r < rows; r++) {
    let x = r % 2 === 0 ? 0 : -30
    while (x < w) {
      const sw = 55 + rand() * 60
      const y = r * stoneH
      const grey = 95 + rand() * 55
      const warm = 8 + rand() * 12
      ctx.fillStyle = `rgb(${grey + warm},${grey},${grey - warm})`
      const inset = 4
      ctx.beginPath()
      ctx.moveTo(x + inset + rand() * 4, y + inset)
      ctx.lineTo(x + sw - inset - rand() * 4, y + inset + rand() * 3)
      ctx.lineTo(x + sw - inset, y + stoneH - inset - rand() * 3)
      ctx.lineTo(x + inset + rand() * 3, y + stoneH - inset)
      ctx.closePath()
      ctx.fill()
      // ombrage bas de pierre
      ctx.fillStyle = 'rgba(0,0,0,0.18)'
      ctx.fillRect(x + inset, y + stoneH - inset - 5, sw - inset * 2, 5)
      x += sw
    }
  }

  for (let i = 0; i < 700; i++) {
    ctx.fillStyle = `rgba(${rand() > 0.5 ? '255,245,230' : '0,0,0'},${rand() * 0.06})`
    ctx.fillRect(rand() * w, rand() * h, 1.6, 1.6)
  }

  return makeRepeatingTexture(canvas, 1.5, 1.5)
}

/** Paysage de montagne enneigée nocturne, peint pour remplir la fenêtre du chalet. */
export function createMountainViewTexture() {
  const canvas = document.createElement('canvas')
  canvas.width = 512
  canvas.height = 640
  const ctx = canvas.getContext('2d')!
  const w = canvas.width
  const h = canvas.height
  const rand = seededRandom(2024)

  // ciel nocturne dégradé
  const sky = ctx.createLinearGradient(0, 0, 0, h)
  sky.addColorStop(0, '#0e1b33')
  sky.addColorStop(0.55, '#22355c')
  sky.addColorStop(1, '#3d5480')
  ctx.fillStyle = sky
  ctx.fillRect(0, 0, w, h)

  // étoiles
  for (let i = 0; i < 90; i++) {
    ctx.fillStyle = `rgba(255,255,255,${0.3 + rand() * 0.7})`
    const size = rand() > 0.9 ? 2.2 : 1.2
    ctx.fillRect(rand() * w, rand() * h * 0.5, size, size)
  }

  // lune
  ctx.fillStyle = '#e8ecf5'
  ctx.beginPath()
  ctx.arc(w * 0.74, h * 0.16, 34, 0, Math.PI * 2)
  ctx.fill()
  ctx.fillStyle = 'rgba(232,236,245,0.25)'
  ctx.beginPath()
  ctx.arc(w * 0.74, h * 0.16, 48, 0, Math.PI * 2)
  ctx.fill()

  // massif lointain
  ctx.fillStyle = '#2c3f63'
  ctx.beginPath()
  ctx.moveTo(-10, h * 0.62)
  ctx.lineTo(w * 0.22, h * 0.4)
  ctx.lineTo(w * 0.48, h * 0.58)
  ctx.lineTo(w * 0.72, h * 0.42)
  ctx.lineTo(w + 10, h * 0.6)
  ctx.lineTo(w + 10, h)
  ctx.lineTo(-10, h)
  ctx.closePath()
  ctx.fill()

  // neige sur le massif lointain
  ctx.fillStyle = '#c9d4e8'
  ctx.beginPath()
  ctx.moveTo(w * 0.22, h * 0.4)
  ctx.lineTo(w * 0.3, h * 0.47)
  ctx.lineTo(w * 0.25, h * 0.475)
  ctx.lineTo(w * 0.18, h * 0.44)
  ctx.closePath()
  ctx.fill()
  ctx.beginPath()
  ctx.moveTo(w * 0.72, h * 0.42)
  ctx.lineTo(w * 0.79, h * 0.48)
  ctx.lineTo(w * 0.73, h * 0.49)
  ctx.lineTo(w * 0.66, h * 0.46)
  ctx.closePath()
  ctx.fill()

  // premier plan : pente enneigée + sapins
  ctx.fillStyle = '#dde5f2'
  ctx.beginPath()
  ctx.moveTo(-10, h * 0.8)
  ctx.quadraticCurveTo(w * 0.4, h * 0.68, w + 10, h * 0.82)
  ctx.lineTo(w + 10, h)
  ctx.lineTo(-10, h)
  ctx.closePath()
  ctx.fill()

  for (let i = 0; i < 9; i++) {
    const tx = rand() * w
    const ty = h * (0.74 + rand() * 0.1)
    const th = 30 + rand() * 40
    ctx.fillStyle = '#1c2c48'
    ctx.beginPath()
    ctx.moveTo(tx, ty - th)
    ctx.lineTo(tx + th * 0.36, ty)
    ctx.lineTo(tx - th * 0.36, ty)
    ctx.closePath()
    ctx.fill()
    ctx.fillStyle = 'rgba(221,229,242,0.5)'
    ctx.beginPath()
    ctx.moveTo(tx, ty - th)
    ctx.lineTo(tx + th * 0.2, ty - th * 0.45)
    ctx.lineTo(tx - th * 0.2, ty - th * 0.45)
    ctx.closePath()
    ctx.fill()
  }

  const texture = new CanvasTexture(canvas)
  texture.colorSpace = SRGBColorSpace
  texture.anisotropy = 4
  texture.needsUpdate = true
  return texture
}
