# QuaternionCompressor

A class used to compress quaternion, it is self included in one header, the QuaternionCompressor.h

## Usage

Very easy to use, is a "Brutal" way but enough for some uses.

- SCALAR
	- Call QuaternionCompressor::Compress and pass 4 quaternion parameters in order to get the 32 bit compressed value 
	- Call QuaternionCompressor::Uncompress passing the compressed value and the 4 quaternion parameters in output to get back the quaternion itself.

- SSE
	- Call QuaternionCompressor::Compress and pass a _m128 parameter in order to get the 32 bit compressed value 
	- Call QuaternionCompressor::Uncompress passing the compressed value and the _m128 parameter in output to get back the quaternion itself.

## Test

You can see the test in main.cpp file


# Build Status

| Platform | Build Status |
|:--------:|:------------:|
| Windows (Visual Studio 2015) | [![Windows Build Status](https://ci.appveyor.com/api/projects/status/github/kabalmcblade/quaternioncompressor?branch=master&svg=true)](https://ci.appveyor.com/project/kabalmcblade/quaternioncompressor) |