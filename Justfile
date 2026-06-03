
set shell := ["powershell.exe", "-c"]

default: main

main:
	meson setup build
	meson compile -C build
	cp build\main.exe main.exe
	.\main.exe

host:
	python -m http.server -d docs
