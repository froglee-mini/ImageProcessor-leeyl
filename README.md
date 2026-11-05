# ImageProcessor 과제 제출

## 구현 항목

- Grayscale
- Brightness
- contrast
- threshold
- Convolution
- Histogram
- crop
- resize
- flip

## 실행 명령어 (예시)


## 필터별 실행 예시

### 1. Grayscale (흑백 변환)
```powershell
.\ImageProcessor.exe -i "C:\test\1_astronaut.bmp" -o "C:\test\grayscale.bmp" -f grayscale
```

### 2. Brightness / Contrast (밝기 및 대비 조절)
```powershell
.\ImageProcessor.exe -i "C:\test\1_astronaut.bmp" -o "C:\test\brightness.bmp" -f brightness:50
```

```powershell
.\ImageProcessor.exe -i "C:\test\1_astronaut.bmp" -o "C:\test\contrast.bmp" -f contrast:1.5
```

### 3. Threshold (이진화)
```powershell
.\ImageProcessor.exe -i "C:\test\1_astronaut.bmp" -o "C:\test\threshold.bmp" -f threshold:128
```

### 4. Convolution (컨볼루션)
```powershell
.\ImageProcessor.exe -i "C:\test\1_astronaut.bmp" -o "C:\test\blur.bmp" -f blur
```

```powershell
.\ImageProcessor.exe -i "C:\test\1_astronaut.bmp" -o "C:\test\sharpen.bmp" -f sharpen
```

### 5. Histogram (히스토그램 출력)
```powershell
.\ImageProcessor.exe -i "C:\test\1_astronaut.bmp" -o "C:\test\histogram.bmp" -f histogram
```

### 6. Crop / Resize (자르기 및 크기 변경)
```powershell
.\ImageProcessor.exe -i "C:\test\1_astronaut.bmp" -o "C:\test\crop.bmp" -f crop:50,50,200,200
```

```powershell
.\ImageProcessor.exe -i "C:\test\1_astronaut.bmp" -o "C:\test\resize.bmp" -f resize:256,256
```

### 7. Flip (이미지 반전)
```powershell
.\ImageProcessor.exe -i "C:\test\1_astronaut.bmp" -o "C:\test\flip_horizontal.bmp" -f flip-horizontal
```

```powershell
.\ImageProcessor.exe -i "C:\test\1_astronaut.bmp" -o "C:\test\flip_vertical.bmp" -f flip-vertical
```


```powershell
# 다중필터
.\ImageProcessor.exe -i "C:\test\input.bmp" -o "C:\test\pipeline.bmp" --pipeline "grayscale,sharpen"
.\ImageProcessor.exe -i "C:\test\input.bmp" -o "C:\test\crop_resize.bmp" --pipeline "crop:50,50,200,200|resize:256,256"
```

```powershell
# 다중스레드
.\ImageProcessor.exe -i "C:\test\input.bmp" -o "C:\test\gray_1.bmp" -f grayscale:1
.\ImageProcessor.exe -i "C:\test\input.bmp" -o "C:\test\gray_4.bmp" -f grayscale:4
```
