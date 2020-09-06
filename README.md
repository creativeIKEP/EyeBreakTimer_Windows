# EyeBreakTimer_Windows
![](https://github.com/creativeIKEP/EyeBreakTimer_Windows/workflows/MSBuild/badge.svg)

![toolbar](/screenshot/toolbar.png) ![setting](/screenshot/setting.png) ![notification](/screenshot/notification.png)

Eye Break Timer is an app reside in Windows tool bar for suppressing eye fatigue caused by long working hours.
This app notify you the break time after setting time expires.
It does not interfere your work because it is Windows resident apptication.
In addition, application timer is started, stopped, and reset by linking with PC lock automatically.

### Support Language
- Japanese
- English

### Install
1. Download insaller(`.msi` or `.exe` file) from [releases](https://github.com/creativeIKEP/EyeBreakTimer_Windows/releases/latest) page and execute.
2. Start Eye Break Timer app!

\* If you use MacOS, you can install from [Mac App Store](https://apps.apple.com/jp/app/eye-break-timer/id1299583418).

### Usage
- You can see menu when you can click app icon on Windows tool bar.
- You can check time, Reset timer with minutes, Pause & Restart, Open setting window, and exit app.
- You can set custom time and "linking functions with PC lock" from setting window.
(Setting window properties are saved in `C:\Users\<user name>\AppData\Roaming\Eye Break Timer\Setting.ini`.)
- You can turn off so that app can't start up in PC login by bellow method.

1. Go to Windows Setting App.
```
Start -> Settings -> Apps -> Startup
```
2. Turn off Eye Break Timer

### Author
[IKEP](https://ikep.jp)

### LICENSE
Copyright (c) 2020 IKEP

[MIT](/LICENSE)

\* **Apply the MIT license to the source code only. It does not include images.**
