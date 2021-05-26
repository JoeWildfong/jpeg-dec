#pragma once

#if __SYS_BIG_ENDIAN == 1
#   define htoms(x) (x)
#   define htoml(x) (x)
#   define mtohs(x) (x)
#   define mtohl(x) (x)
#else
#   define htoms(x) (((x)>>8)|((x)<<8))
#   define htoml(x) (((x)<<24)|(((x)&0xFF00)<<8)|(((x)&0xFF0000)>>8)|((x)>>24))
#   define mtohs(x) (((x)>>8)|((x)<<8))
#   define mtohl(x) (((x)<<24)|(((x)&0xFF00)<<8)|(((x)&0xFF0000)>>8)|((x)>>24))
#endif