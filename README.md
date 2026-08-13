# STM32F401CCU6 LED Blink Test Project

> [!NOTE]  
> **Trạng thái:** Chạy thành công (Đã kiểm tra, biên dịch và nạp thực tế vào board qua ST-LINK ngày 13/08/2026).

Dự án này là chương trình mẫu hoàn chỉnh dùng để kiểm tra tính năng GPIO và hoạt động cơ bản của board phát triển **STM32F401CCU6 (WeAct Black Pill)** sử dụng thư viện **STM32Cube HAL**.

---

## 📌 Thông tin cấu hình

| Thông số | Cấu hình |
|---|---|
| **MCU** | STM32F401CCU6 (ARM Cortex-M4 @ 84MHz) |
| **LED Onboard** | **PC13** |
| **Mức tích cực LED** | **Active LOW** (Mức `0` / `RESET` = Bật LED, Mức `1` / `SET` = Tắt LED) |
| **Clock chính (SYSCLK)** | **84 MHz** (Sử dụng thạch anh ngoài HSE 25MHz đi qua PLL) |
| **Framework** | STM32Cube HAL (Không sử dụng Arduino / PlatformIO) |

---

## 🔌 Sơ đồ kết nối nạp mạch (SWD)

Để nạp code và debug, kết nối mạch nạp **ST-LINK V2** với board qua giao tiếp SWD:

| Chân ST-LINK | Chân trên STM32F401CCU6 Board |
|---|---|
| **SWDIO** | **PA13** |
| **SWCLK** | **PA14** |
| **GND** | **GND** |
| **3.3V (VTREF)**| **VDD / 3.3V** |
| **RST (Tùy chọn)**| **NRST** |

---

## 📁 Cấu trúc thư mục dự án

```text
stm32f401ccu6/
├── Core/
│   ├── Inc/
│   │   ├── main.h                   # Định nghĩa chân LED (PC13)
│   │   ├── stm32f4xx_hal_conf.h     # Cấu hình module HAL (GPIO, RCC, v.v.)
│   │   └── stm32f4xx_it.h           # Khai báo các hàm ngắt
│   └── Src/
│       ├── main.c                   # Hàm main() & cấu hình clock, vòng lặp blink
│       ├── stm32f4xx_it.c           # Trình xử lý ngắt (bao gồm SysTick cho HAL_Delay)
│       └── stm32f4xx_hal_msp.c      # Khởi tạo mức thấp (MSP) cho ngoại vi
├── Drivers/                         # Driver CMSIS và STM32F4xx HAL
├── build/                           # Thư mục chứa các file sau khi biên dịch (.elf, .bin, .hex)
├── STM32F401CCUx_FLASH.ld           # Linker Script (Phân bổ vùng nhớ FLASH 256KB, RAM 64KB)
├── STM32F401CCU6_LED.ioc            # File cấu hình cấu hình CubeMX
└── Makefile                         # File cấu hình build dự án bằng Make
```

---

## 🛠️ Hướng dẫn Biên dịch và Nạp Code

### 1. Biên dịch dự án
Nếu sử dụng môi trường dòng lệnh (như MSYS2 có sẵn GCC toolchain `arm-none-eabi-gcc` và `make`):

```powershell
# Thiết lập đường dẫn môi trường (nếu cần) và build
$env:PATH = "C:\msys64\mingw64\bin;C:\msys64\usr\bin;" + $env:PATH
make clean all
```

Kết quả biên dịch sẽ sinh ra các file định dạng `.elf`, `.hex`, và `.bin` trong thư mục `build/`.

### 2. Nạp code qua STM32CubeProgrammer
Sử dụng công cụ dòng lệnh **STM32CubeProgrammer** để nạp trực tiếp file `.bin` xuống chip:

```powershell
& "C:\Program Files\STMicroelectronics\STM32Cube\STM32CubeProgrammer\bin\STM32_Programmer_CLI.exe" -c port=SWD -w "build\STM32F401CCU6_LED.bin" 0x08000000 -v -rst
```

---

## 🎯 Hoạt động thực tế

Sau khi nạp thành công:
1. Chip tự động reset.
2. LED PC13 onboard trên mạch sẽ **nhấp nháy với chu kỳ 1 giây** liên tục (500ms Sáng - 500ms Tắt).

---

## 🏢 Thông tin đơn vị phát triển & Hỗ trợ

* **Đơn vị phát triển:** Công ty TNHH Công nghệ Chipxa
* **Mã số thuế:** 0111399950
* **Email:** [support@chipxa.vn](mailto:support@chipxa.vn)
* **Liên hệ hỗ trợ kỹ thuật:** 0971399950