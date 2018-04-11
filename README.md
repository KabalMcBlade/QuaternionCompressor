# QuaternionCompressor

A class used to compress quaternion, it is self included in one header, the QuaternionCompressor.h

## Important

For now it works just iwth x86 architecture dure a couple of mmx call that actually doesn't exists in the x64 architecture!

## Usage

Very easy to use, is a "Brutal" way but enough for some uses.

- Call QuaternionCompressor::Compress and pass 4 quaternion parameters in order to get the 32 bit compressed value 
- Call QuaternionCompressor::Uncompress passing the compressed value and the 4 quaternion parameters in output to get back the quaternion itself.

The function now support SIMD version of a quaternion: _m128
(WORK IN PROGRESS, for now support only the compression!)

## Test

You can see the test in main.cpp file


# Build Status

| Platform | Build Status |
|:--------:|:------------:|
| Windows (Visual Studio 2015) | [![Windows Build Status](https://ci.appveyor.com/api/projects/status/github/kabalmcblade/quaternioncompressor?branch=master&svg=true)](https://ci.appveyor.com/project/kabalmcblade/quaternioncompressor) |