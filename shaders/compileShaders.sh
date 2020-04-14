#!/bin/bash

mkdir -p ../build/shaders

glslc shader.vert -o ../build/shaders/vert.spv
glslc shader.frag -o ../build/shaders/frag.spv