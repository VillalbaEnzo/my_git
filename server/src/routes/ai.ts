import express from 'express';

const router = express.Router();

router.post('/ask', async (req, res) => {
  try {
    const { question } = req.body;

    const aiResponse = await fetch('http://localhost:8001/generate', {
      method: 'POST',
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify({
        prompt: question,
        model: "llama3"
      })
    });

    const data = await aiResponse.json();
    res.json(data);

  } catch (error) {
    console.error(error);
    res.status(500).json({ error: "Erreur de communication avec le service IA" });
  }
});

export default router;