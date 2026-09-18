# 🌿 SmartHerbalNet

### IoT-Assisted Environmental Data Collection and Leaf Disease Prediction Through Transfer Learning

SmartHerbalNet is a field-developed AI and IoT-based smart herbal farming system designed to detect diseases in herbal plant leaves while continuously monitoring environmental conditions in real time.

Unlike a purely laboratory-based image classification study, this project was developed through field-level data collection, stakeholder interaction, hardware implementation, environmental sensing, and AI model development.

The project combines:

- 📷 Field-collected herbal leaf images
- 🤖 Transfer learning-based disease prediction
- 🌱 Real-time environmental monitoring
- 🔌 ESP32-based sensor acquisition
- 📸 Raspberry Pi camera integration
- ☁️ Cloud-based data transmission and monitoring
- 🚨 Environmental condition alerts
- 📱 Farmer-oriented monitoring interface

> **Project Type:** Capstone Project  
> **Funding:** University-funded Project  
> **Data Collection:** Field-collected by the project team  
> **Location:** Gazipur, Bangladesh  
> **Herbal Plants:** 9  
> **Total Leaf Images:** 5,398  
> **Healthy Images:** 2,629  
> **Diseased Images:** 2,769

## 📌 Project Overview

SmartHerbalNet was developed to address the practical challenges faced in herbal plant cultivation, where leaf diseases and unfavorable environmental conditions can reduce crop quality, productivity, and market value.

The project was developed through direct field investigation in a herbal plant village in Gazipur, Bangladesh. We visited the farming area, interacted with local growers and business owners, and collected practical information regarding medicinal plants that are economically important, widely cultivated, and commonly affected by diseases.

Based on these field observations, stakeholder recommendations, and supporting literature, nine herbal plants were selected:

**Arosh Kalai, Bel, Neem, Sojina (Moringa), Tulsi, Basok, Chirota, Pathor Khuchi, and Thankuni.**

The resulting dataset contains **5,398 field-collected leaf images**, including **2,629 healthy** and **2,769 diseased** samples. Images were collected under natural field conditions using an **Apple iPhone 15** smartphone.

The AI component is integrated with an IoT-based environmental monitoring system using sensors and an ESP32 platform, while Raspberry Pi and camera hardware support image acquisition and disease prediction.

The overall goal is to demonstrate an end-to-end, practical smart farming framework rather than a standalone classification model.

## 🌱 Why These Plants Were Selected

The nine herbal plants were selected based on a combination of:

- Field observations
- Direct recommendations from local growers
- Discussions with herbal plant business owners
- Medicinal importance
- Economic relevance
- Local cultivation practices
- Disease prevalence
- Potential impact of disease on crop quality and market value

This selection process was carried out during our field visit to a herbal plant village in Gazipur, Bangladesh.

The field visit was an important part of the project because it allowed us to understand the practical farming environment, identify relevant plant species, observe disease conditions, and design the dataset around real cultivation practices rather than relying only on publicly available datasets.
## 📷 Field Data Collection

One of the major contributions of SmartHerbalNet is the development of an original field-collected herbal leaf image dataset.

The images were collected directly from herbal cultivation environments rather than being assembled solely from existing public datasets.

### Data Collection Process

1. Visited a herbal plant cultivation area in Gazipur, Bangladesh.
2. Interacted with local herbal plant growers and business owners.
3. Identified medicinal plants with practical and economic relevance.
4. Observed healthy and diseased leaves under natural field conditions.
5. Captured leaf images using an Apple iPhone 15.
6. Organized the collected images according to plant type and disease/health condition.
7. Prepared the dataset for AI-based classification and evaluation.

### 📊 Dataset at a Glance

| Category | Value |
|---|---:|
| Herbal plant groups | 9 |
| Total images | 5,398 |
| Healthy images | 2,629 |
| Diseased images | 2,769 |
| Collection environment | Natural field conditions |
| Camera | Apple iPhone 15 |
| Collection location | Gazipur, Bangladesh |

### Dataset Distribution

| Plant | Healthy | Diseased | Total |
|---|---:|---:|---:|
| Arosh Kalai | 324 | 292 | 616 |
| Basok | 278 | 482 | 760 |
| Bel | 312 | 267 | 579 |
| Chirota | 317 | 244 | 561 |
| Neem | 278 | 327 | 605 |
| Pathor Khuchi | 317 | 280 | 597 |
| Sojina (Moringa) | 264 | 283 | 547 |
| Thankuni | 281 | 314 | 595 |
| Tulsi | 258 | 280 | 538 |
| **Total** | **2,629** | **2,769** | **5,398** |
