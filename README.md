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

## 📷 Exemples Illustrés

### **1️⃣ Détection d'une Forme dans une Image**
L'algorithme repère une forme spécifique dans une image.

🔹 **Image d’entrée**  
![Exemple 1 - Image d’entrée](https://via.placeholder.com/300)

🔹 **Résultat après corrélation**  
![Exemple 1 - Résultat](https://via.placeholder.com/300)

---

### **2️⃣ Application sur une Image Satellite**
Utilisation de la corrélation pour repérer un motif sur une image satellite.

🔹 **Image satellite originale**  
![Exemple 2 - Image Satellite](https://via.placeholder.com/300)

🔹 **Zone détectée (carré rouge sur la cible)**  
![Exemple 2 - Détection](https://via.placeholder.com/300)

---

## 🛠️ Installation et Utilisation
### **🔹 Prérequis**
- Python 3.x
- `numpy`, `opencv`, `matplotlib`, `scipy`

Installez les dépendances avec :
```sh
pip install numpy opencv-python matplotlib scipy
