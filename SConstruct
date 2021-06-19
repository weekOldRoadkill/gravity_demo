# -- Imports --
from platform import system as os
from os import system
# -------------




# -- Arguments --
warn = [
	"-Wall",
	"-Werror",
	"-Wextra",
	"-Wno-unused-variable"
]


gen = [
	"-m64",
	"-flto",
	"-Ofast",
	"-std=c99",
	"-march=native",
	"-mtune=native"
]


comp = [
	"-xc"
]


link = [
	"-s",
	"-fuse-ld=lld"
]


lib = [
	"m",
	"dl",
	"GL",
	"X11",
	"pthread",
	"glfw3nix"
]


lib_path = [
	"src/glfw"
]


include_path = [
	"src/glad",
	"src/glfw"
]


if(os() == "Linux"):
	system("clear")
else:
	print("%s is not supported."%os())
	exit(0x00)
# ---------------




# -- Building --
env = Environment(
	LIBS = lib,
	CC = "clang",
	LINK = "clang",
	LIBPATH = lib_path,
	CPPPATH = include_path,
	CCFLAGS = warn+gen+comp,
	LINKFLAGS = warn+gen+link
)


testing = env.Program(
	target = "build/gravity_demo",
	source = Glob("src/*.c")+Glob("src/glad/*.c")
)
# --------------