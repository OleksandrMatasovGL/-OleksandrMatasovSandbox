// Copyright 2020 Oleksandr Matasov

#pragma once
#include <anyrpc/error.h>
#include <anyrpc/value.h>

using anyrpc::AnyRpcException;
using anyrpc::Value;

// Define the method functions that can be called
void Add(Value &params, Value &result) {
  if ((!params.IsArray()) || (params.Size() != 2) || (!params[0].IsNumber()) ||
      (!params[1].IsNumber()))
    throw AnyRpcException(anyrpc::AnyRpcErrorInvalidParams,
                          "Invalid parameters");
  result = params[0].GetDouble() + params[1].GetDouble();
}
