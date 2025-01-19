# 🎯 Reconnaissance des Formes par Corrélation d'Images

Ce projet utilise la **Transformée de Fourier Rapide (FFT)** pour détecter et localiser des formes spécifiques dans des images bitmap.

## 📌 Objectifs
- Importer des images bitmap contenant les formes recherchées et l’image cible.
- Effectuer une **corrélation** dans l’espace de Fourier pour identifier les formes.
- Optimiser les calculs grâce à la **FFT 2D**.
- Afficher les résultats sous forme d’image ou de texte.

## 🔬 Méthodologie
1. **Chargement des images** (forme cible + image principale).
2. **Application de la Transformée de Fourier (FFT)**.
3. **Corrélation des données en domaine fréquentiel**.
4. **Détection du maximum pour localiser la forme**.

