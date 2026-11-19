import { CanvasTexture, SRGBColorSpace } from 'three'

/** Plaque de laiton gravée : fond métal chaud, biseau, texte en creux, deux vis. */
export function createPlateTexture(label: string) {
  const canvas = document.createElement('canvas')
  canvas.width = 512
  canvas.height = 64
  const ctx = canvas.getContext('2d')!
  const w = canvas.width
  const h = canvas.height

  const metal = ctx.createLinearGradient(0, 0, 0, h)
  metal.addColorStop(0, '#d4af6a')
  metal.addColorStop(0.5, '#b8923f')
  metal.addColorStop(1, '#96742c')
  ctx.fillStyle = metal
  ctx.fillRect(0, 0, w, h)

  // biseau
  ctx.strokeStyle = 'rgba(255,240,200,0.9)'
  ctx.lineWidth = 3
  ctx.strokeRect(3, 3, w - 6, h - 6)
  ctx.strokeStyle = 'rgba(70,50,10,0.7)'
  ctx.lineWidth = 2
  ctx.strokeRect(7, 7, w - 14, h - 14)

  // vis
  for (const x of [18, w - 18]) {
    ctx.beginPath()
    ctx.arc(x, h / 2, 6, 0, Math.PI * 2)
    ctx.fillStyle = '#8a6a24'
    ctx.fill()
    ctx.strokeStyle = 'rgba(50,35,8,0.8)'
    ctx.lineWidth = 1.5
    ctx.stroke()
    ctx.beginPath()
    ctx.moveTo(x - 4, h / 2)
    ctx.lineTo(x + 4, h / 2)
    ctx.stroke()
  }

  // texte gravé : ombre claire en dessous, texte sombre par-dessus
  ctx.textAlign = 'center'
  ctx.textBaseline = 'middle'
  const text = label.toUpperCase()
  let size = 30
  ctx.font = `600 ${size}px "Georgia", serif`
  const maxWidth = w - 90
  const measured = ctx.measureText(text).width
  if (measured > maxWidth) {
    size = Math.max(14, Math.floor((size * maxWidth) / measured))
    ctx.font = `600 ${size}px "Georgia", serif`
  }
  ctx.fillStyle = 'rgba(255,240,200,0.55)'
  ctx.fillText(text, w / 2, h / 2 + 2.5)
  ctx.fillStyle = '#4a3410'
  ctx.fillText(text, w / 2, h / 2 + 1)

  const texture = new CanvasTexture(canvas)
  texture.colorSpace = SRGBColorSpace
  texture.anisotropy = 4
  texture.needsUpdate = true
  return texture
}
