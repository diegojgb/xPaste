# xPaste

<img src="https://github.com/diegojgb/xPaste/blob/main/screenshots/screenshot1.png" width="828" height="584">
<img src="https://github.com/diegojgb/xPaste/blob/main/screenshots/screenshot2.png" width="828" height="584">

## What is it?

xPaste is a simple application that allows you to bypass paste-blocking websites and applications by simulating keystrokes and typing the text from your clipboard.

## Installation

- You can download the latest release from [here](https://github.com/diegojgb/xPaste/releases/latest "https://github.com/diegojgb/xPaste/releases/latest")
- To run the application, you must have the [Visual C++ Redistributable](https://learn.microsoft.com/en-us/cpp/windows/latest-supported-vc-redist "https://learn.microsoft.com/en-us/cpp/windows/latest-supported-vc-redist") installed on your system.

## Usage
1. &nbsp;Open xPaste and make sure it's turned on.  
2. &nbsp;Copy the text you want to paste.  
3. &nbsp;Press CTRL+V (or your customized hotkey).  
4. &nbsp;The text will be typed, with simulated keystrokes.  

It comes with a few settings you can play around with, nothing special.

## Source dependencies

If you want to work on the application and build it by yourself using Qt Creator, Visual Studio, or your preferred method, you need to include this dependency on your project:

- [WinToast](https://github.com/mohabouje/WinToast "https://github.com/mohabouje/WinToast") - by [mohabouje](https://github.com/mohabouje "https://github.com/mohabouje").

The CMakeLists.txt already includes WinToast as a subdirectory, so you just have to clone WinToast's repository and place it inside the root folder, along with WatchLog's CMakeLists.txt.