import { FileUp } from 'lucide-react'

interface FileFieldProps {
  id: string
  label: string
  file: File | null
  onChange: (file: File | null) => void
  accept: string
  hint: string
}

export default function FileField({ id, label, file, onChange, accept, hint }: FileFieldProps) {
  return (
    <div>
      <label className="mb-1.5 block text-sm font-medium text-stone-700 dark:text-stone-300">{label}</label>
      <label
        htmlFor={id}
        className="flex cursor-pointer items-center justify-center gap-2 rounded-lg border border-dashed border-cobalt-500/40 bg-cobalt-500/[0.06] px-4 py-3 text-sm font-medium text-cobalt-700 transition-colors hover:border-cobalt-500/70 hover:bg-cobalt-500/10 dark:text-cobalt-300"
      >
        <FileUp size={16} strokeWidth={1.75} />
        <span className="truncate">{file ? file.name : 'Choisir un document'}</span>
      </label>
      <input
        id={id} type="file" accept={accept} className="hidden"
        onChange={(e) => onChange(e.target.files?.[0] ?? null)}
      />
      <span className="mt-1 block text-xs text-stone-500">{hint}</span>
    </div>
  )
}
