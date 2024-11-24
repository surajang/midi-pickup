# MIDI-pickup

## Goal

Roland GK-5, Fishman Triple play처럼 일렉트릭 기타의 신호를 MIDI signal로 변환하는 장비를 DIY 해보는 Weekend project 입니다.

## Target spec.
- Low latency
- Pitch to MIDI note on/off message 변환
- Vibrato 동작을 Pitch bend CC message로 변환
- 음의 크기를 velocity로 변환
- 6-Poly (한 번에 6개 넘는 노트가 들어올 리는 없으니..)

## 기본 설계 초안
> 대충 이렇게 구성될 거 같음.

### 각 현 별로 분리된 transducer 6개
- 각 현마다 센서를 장치하여 개별 진동을 얻을 수 있도록 한다.
- 이 신호를 직접 audio로 쓸 것은 아니기 때문에 음색보다는 정확하고 robust한 수음이 가능한 것으로.
- 별도 전원 필요 없는 passive type이면 좋겠음.

### Transducer에서 받은 신호의 pre-amp 
- 수집한 신호를 처리 가능한 수준으로 증폭하는 프리앰프 6채널
- unity gain buffer가 될지, 어느 정도 감도 조절이 필요할지는 실험을 통해 적용.

### 증폭된 신호의 분석
- 입력 신호에서 Note, Pitch bend, Velocity를 얻는다. (어떻게???)
  - Note 범위: MIDI note number 0 - 127
    - E-standard tuning 24 fret 기타의 발성 가능 범위가 E2 ~ E7(40 ~ 100)이니 충분
    - 테스트해서 성능 안나오는 끝 영역은 제외
    - 입력신호를 FFT해서 1st harmonic(fundamental)의 진동수 구하기
    - 이 진동수를 https://inspiredacoustics.com/en/MIDI_note_numbers_and_center_frequencies 의 테이블에서 가장 가까운 note로 변환하기
  - 변환된 note의 진동수와 실제 입력 진동수의 차이만큼을 pitch bend로 변환하기 (몇 cent up or down?)
  - 입력 신호의 세기(RMS? ADC reading값?)를 velocity 0 - 127로 변환
  - Note on/off의 구분
    - 각 현 별로 한 번에 하나의 note만 가능하므로 이전과 note가 바뀌면 이전 것을 off, 최신 것을 on으로 판단한다.
    - 동일 note에 대해서는 velocity, pitch bend만 track 한다 (어떻게?)

### 분석된 note, pitch bend, velocity를 MIDI message로 전송
- 이왕이면 USB-MIDI로.. (DIN-5 단자가 흔하지 않음)

## Hardware

### Piezo pickup saddle
- Magnetic보다 piezo가 장착이 더 용이할 듯
- 예전 Brian Moore에서 쓰던 RMC piezo 처럼 retrofit 가능한 saddle에 센서가 장착된 것 찾음
- https://www.amazon.com/dp/B0CSD3R3YF?ref_=ppx_hzod_title_dt_b_fed_asin_title_0_0

### Preamp
- Quad op-amp 2개 (LM248 구입)
  - 2채널 남는 건 다른 용도로도 쓸 수 있을 듯

### Controller
- Teensy 4.0
  - Analog 입력 6개 사용 가능
  - 600MHz clock speed - FFT 빠르게 가능할 듯
  - Audio, MIDI library 지원
  - USB bus power로 구동 가능
  - Arduino 개발 환경 사용 가능
  - 3만원 미만으로 살 수 있다!
