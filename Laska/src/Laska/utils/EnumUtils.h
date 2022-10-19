#pragma once

#define FlagI32(flag) (int32_t)1 << flag
#define FlagI64(flag) (int64_t)1 << flag
#define FlagUI32(flag) (uint32_t)1 << flag
#define FlagUI64(flag) (uint64_t)1 << flag

#define HasFlagI32(value, flag) value & FlagI32(flag)
#define HasFlagI64(value, flag) value & FlagI64(flag)
#define HasFlagUI32(value, flag) value & FlagUI32(flag)
#define HasFlagUI64(value, flag) value & FlagUI64(flag)
