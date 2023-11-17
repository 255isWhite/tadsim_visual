#!/bin/bash

MSG_DIR=$(dirname $0)

for f in $MSG_DIR/*.proto
do
  protoc -I=$MSG_DIR --cpp_out=$MSG_DIR $f
done

GRPC_CPP_PLUGIN=`which grpc_cpp_plugin`

protoc -I=$MSG_DIR --grpc_out=$MSG_DIR --plugin=protoc-gen-grpc=$GRPC_CPP_PLUGIN $MSG_DIR/coordinatorService.proto
protoc -I=$MSG_DIR --grpc_out=$MSG_DIR --plugin=protoc-gen-grpc=$GRPC_CPP_PLUGIN $MSG_DIR/simDriverService.proto
protoc -I=$MSG_DIR --grpc_out=$MSG_DIR --plugin=protoc-gen-grpc=$GRPC_CPP_PLUGIN $MSG_DIR/simAgent.proto
protoc -I=$MSG_DIR --grpc_out=$MSG_DIR --plugin=protoc-gen-grpc=$GRPC_CPP_PLUGIN $MSG_DIR/xil_interface.proto
