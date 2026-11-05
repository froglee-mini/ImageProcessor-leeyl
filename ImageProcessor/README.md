#ImageProcessor
## 1. 소개
7개의 필터가 탑재된 이미지를 처리하는 CLI 기반 프로그램입니다.

## 2. 개발환경
언어 : C++17
IDE  : visual studio 2022
운영체제 : windows

## 구현 기능
- Grayscale
- Brightness
- contrast
- threshold
- Convolution
- Histogram
- crop
- resize
- flip

## 실행예시

- 단일 필터
.\ImageProcessor.exe -i "C:\test\input.bmp" -o "C:\test\gray.bmp" -f grayscale
.\ImageProcessor.exe -i "C:\test\input.bmp" -o "C:\test\bright.bmp" -f brightness:30
.\ImageProcessor.exe -i "C:\test\input.bmp" -o "C:\test\binary.bmp" -f threshold:128

- 다중 필터
.\ImageProcessor.exe -i "C:\test\input.bmp" -o "C:\test\pipeline.bmp" --pipeline "grayscale,sharpen"
.\ImageProcessor.exe -i "C:\test\input.bmp" -o "C:\test\crop_resize.bmp" --pipeline "crop:50,50,200,200|resize:256,256"
여러개의 필터 사용시 입력 순서대로 적용됩니다. 
매개변수에 쉼표가 포함된 필터 사용시 '|'로 필터를 구분해줍니다.
--filter와 --pipeline은 동시에 사용하지 않습니다.

-다중스레드
.\ImageProcessor.exe -i "C:\test\input.bmp" -o "C:\test\gray_1.bmp" -f grayscale:1
.\ImageProcessor.exe -i "C:\test\input.bmp" -o "C:\test\gray_4.bmp" -f grayscale:4
grayscale:(숫자)는 스레드 개수를 지정합니다.

## 참고사항
다중 스레드 효과 검증은 고화질이미지 사용시 확인 가능합니다.