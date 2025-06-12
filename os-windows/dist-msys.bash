#!/bin/bash

cp ../build/app.exe .
./deplister.exe app.exe
cp /c/msys64/mingw64/bin/SDL3.dll .
cp /c/msys64/mingw64/bin/libfreeglut.dll .
