#if 0
//
// Generated by Microsoft (R) D3D Shader Disassembler
//
//
// Input signature:
//
// Name                 Index   Mask Register SysValue  Format   Used
// -------------------- ----- ------ -------- -------- ------- ------
// SV_Position              0   xyzw        0     NONE   float   xyzw
// NORMAL                   0   xyz         1     NONE   float   xyz 
// TEXCOORD                 0   xy          2     NONE   float   xy  
// COLOR                    0   xyzw        3     NONE   float   xyzw
//
//
// Output signature:
//
// Name                 Index   Mask Register SysValue  Format   Used
// -------------------- ----- ------ -------- -------- ------- ------
// COLOR                    0   xyzw        0     NONE   float   xyzw
// COLOR                    1   xyzw        1     NONE   float   xyzw
// TEXCOORD                 0   xy          2     NONE   float   xy  
// SV_Position              0   xyzw        3      POS   float   xyzw
//
//
// Constant buffer to DX9 shader constant mappings:
//
// Target Reg Buffer  Start Reg # of Regs        Data Conversion
// ---------- ------- --------- --------- ----------------------
// c1         cb0             0         4  ( FLT, FLT, FLT, FLT)
// c5         cb0             6         1  ( FLT, FLT, FLT, FLT)
// c6         cb0             9         1  ( FLT, FLT, FLT, FLT)
// c7         cb0            12         1  ( FLT, FLT, FLT, FLT)
// c8         cb0            14         4  ( FLT, FLT, FLT, FLT)
// c12        cb0            19         7  ( FLT, FLT, FLT, FLT)
//
//
// Runtime generated constant mappings:
//
// Target Reg                               Constant Description
// ---------- --------------------------------------------------
// c0                              Vertex Shader position offset
//
//
// Level9 shader bytecode:
//
    vs_2_0
    def c19, 0, 1, 0, 0
    dcl_texcoord v0  // vin<0,1,2,3>
    dcl_texcoord1 v1  // vin<4,5,6>
    dcl_texcoord2 v2  // vin<7,8>
    dcl_texcoord3 v3  // vin<9,10,11,12>

#line 54 "C:\Users\hansh\Downloads\20230725223251_Code\Code\X\External\DirectXTK\Src\Shaders\Lighting.fxh"
    dp4 r0.x, v0, c9  // ::pos_ws<0>
    dp4 r0.y, v0, c10  // ::pos_ws<1>
    dp4 r0.z, v0, c11  // ::pos_ws<2>
    add r0.xyz, -r0, c7
    nrm r1.xyz, r0  // ::eyeVector<0,1,2>

#line 30
    add r0.xyz, r1, -c4
    nrm r1.xyz, r0  // ::halfVectors<0,1,2>

#line 56
    dp3 r0.x, v1, c12
    dp3 r0.y, v1, c13
    dp3 r0.z, v1, c14
    nrm r2.xyz, r0  // ::worldNormal<0,1,2>

#line 34
    dp3 r0.x, r1, r2  // ::dotH<0>
    dp3 r0.y, -c4, r2  // ::dotL<0>

#line 39
    max r0.x, r0.x, c19.x

#line 36
    sge r0.z, r0.y, c19.x  // ::zeroL<0>

#line 39
    mul r0.x, r0.z, r0.x
    mul r0.z, r0.y, r0.z  // ::diffuse<0>

#line 43
    mul r1.xyz, r0.z, c5
    mov r2.xyz, c1  // Parameters::DiffuseColor<0,1,2>
    mad r1.xyz, r1, r2, c2  // ::result<0,1,2>

#line 348 "C:\Users\hansh\Downloads\20230725223251_Code\Code\X\External\DirectXTK\Src\Shaders\BasicEffect.fx"
    mul oT0.xyz, r1, v3  // ::VSBasicOneLightTxVc<0,1,2>

#line 39 "C:\Users\hansh\Downloads\20230725223251_Code\Code\X\External\DirectXTK\Src\Shaders\Lighting.fxh"
    pow r1.x, r0.x, c3.w
    mul r0.x, r0.y, r1.x  // ::specular<0>

#line 44
    mul r0.xyz, r0.x, c6
    mul oT1.xyz, r0, c3  // ::VSBasicOneLightTxVc<4,5,6>

#line 60
    dp4 oPos.z, v0, c17  // ::VSBasicOneLightTxVc<12>

#line 11 "C:\Users\hansh\Downloads\20230725223251_Code\Code\X\External\DirectXTK\Src\Shaders\Common.fxh"
    dp4 r0.x, v0, c8
    max r0.x, r0.x, c19.x
    min oT1.w, r0.x, c19.y  // ::VSBasicOneLightTxVc<7>

#line 348 "C:\Users\hansh\Downloads\20230725223251_Code\Code\X\External\DirectXTK\Src\Shaders\BasicEffect.fx"
    mul oT0.w, v3.w, c1.w  // ::VSBasicOneLightTxVc<3>

#line 60 "C:\Users\hansh\Downloads\20230725223251_Code\Code\X\External\DirectXTK\Src\Shaders\Lighting.fxh"
    dp4 r0.x, v0, c15  // ::vout<0>
    dp4 r0.y, v0, c16  // ::vout<1>
    dp4 r0.z, v0, c18  // ::vout<3>

#line 340 "C:\Users\hansh\Downloads\20230725223251_Code\Code\X\External\DirectXTK\Src\Shaders\BasicEffect.fx"
    mad oPos.xy, r0.z, c0, r0  // ::VSBasicOneLightTxVc<10,11>
    mov oPos.w, r0.z  // ::VSBasicOneLightTxVc<13>

#line 347
    mov oT2.xy, v2  // ::VSBasicOneLightTxVc<8,9>

// approximately 44 instruction slots used
vs_4_0
dcl_constantbuffer CB0[26], immediateIndexed
dcl_input v0.xyzw
dcl_input v1.xyz
dcl_input v2.xy
dcl_input v3.xyzw
dcl_output o0.xyzw
dcl_output o1.xyzw
dcl_output o2.xy
dcl_output_siv o3.xyzw, position
dcl_temps 3
dp3 r0.x, v1.xyzx, cb0[19].xyzx
dp3 r0.y, v1.xyzx, cb0[20].xyzx
dp3 r0.z, v1.xyzx, cb0[21].xyzx
dp3 r0.w, r0.xyzx, r0.xyzx
rsq r0.w, r0.w
mul r0.xyz, r0.wwww, r0.xyzx
dp3 r0.w, -cb0[3].xyzx, r0.xyzx
ge r1.x, r0.w, l(0.000000)
and r1.x, r1.x, l(0x3f800000)
mul r1.y, r0.w, r1.x
mul r1.yzw, r1.yyyy, cb0[6].xxyz
mad r1.yzw, r1.yyzw, cb0[0].xxyz, cb0[1].xxyz
mul o0.xyz, r1.yzwy, v3.xyzx
mul o0.w, v3.w, cb0[0].w
dp4 r2.x, v0.xyzw, cb0[15].xyzw
dp4 r2.y, v0.xyzw, cb0[16].xyzw
dp4 r2.z, v0.xyzw, cb0[17].xyzw
add r1.yzw, -r2.xxyz, cb0[12].xxyz
dp3 r2.x, r1.yzwy, r1.yzwy
rsq r2.x, r2.x
mad r1.yzw, r1.yyzw, r2.xxxx, -cb0[3].xxyz
dp3 r2.x, r1.yzwy, r1.yzwy
rsq r2.x, r2.x
mul r1.yzw, r1.yyzw, r2.xxxx
dp3 r0.x, r1.yzwy, r0.xyzx
max r0.x, r0.x, l(0.000000)
mul r0.x, r1.x, r0.x
log r0.x, r0.x
mul r0.x, r0.x, cb0[2].w
exp r0.x, r0.x
mul r0.x, r0.w, r0.x
mul r0.xyz, r0.xxxx, cb0[9].xyzx
mul o1.xyz, r0.xyzx, cb0[2].xyzx
dp4_sat o1.w, v0.xyzw, cb0[14].xyzw
mov o2.xy, v2.xyxx
dp4 o3.x, v0.xyzw, cb0[22].xyzw
dp4 o3.y, v0.xyzw, cb0[23].xyzw
dp4 o3.z, v0.xyzw, cb0[24].xyzw
dp4 o3.w, v0.xyzw, cb0[25].xyzw
ret 
// Approximately 0 instruction slots used
#endif

const BYTE BasicEffect_VSBasicOneLightTxVc[] =
{
     68,  88,  66,  67, 225,  55, 
     33, 246, 114, 227,  56,  46, 
     72,  45, 126, 106,   7,  63, 
    141,  22,   1,   0,   0,   0, 
    136,  16,   0,   0,   4,   0, 
      0,   0,  48,   0,   0,   0, 
     84,  10,   0,   0, 104,  15, 
      0,   0, 252,  15,   0,   0, 
     65, 111, 110,  57,  28,  10, 
      0,   0,  28,  10,   0,   0, 
      0,   2, 254, 255, 172,   9, 
      0,   0, 112,   0,   0,   0, 
      6,   0,  36,   0,   0,   0, 
    108,   0,   0,   0, 108,   0, 
      0,   0,  36,   0,   1,   0, 
    108,   0,   0,   0,   0,   0, 
      4,   0,   1,   0,   0,   0, 
      0,   0,   0,   0,   6,   0, 
      1,   0,   5,   0,   0,   0, 
      0,   0,   0,   0,   9,   0, 
      1,   0,   6,   0,   0,   0, 
      0,   0,   0,   0,  12,   0, 
      1,   0,   7,   0,   0,   0, 
      0,   0,   0,   0,  14,   0, 
      4,   0,   8,   0,   0,   0, 
      0,   0,   0,   0,  19,   0, 
      7,   0,  12,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   2, 254, 255, 254, 255, 
    202,   1,  68,  66,  85,  71, 
     40,   0,   0,   0, 252,   6, 
      0,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,  72,   1, 
      0,   0,  41,   0,   0,   0, 
     84,   1,   0,   0,  14,   0, 
      0,   0, 228,   5,   0,   0, 
    208,   2,   0,   0,  67,  58, 
     92,  85, 115, 101, 114, 115, 
     92, 104,  97, 110, 115, 104, 
     92,  68, 111, 119, 110, 108, 
    111,  97, 100, 115,  92,  50, 
     48,  50,  51,  48,  55,  50, 
     53,  50,  50,  51,  50,  53, 
     49,  95,  67, 111, 100, 101, 
     92,  67, 111, 100, 101,  92, 
     88,  92,  69, 120, 116, 101, 
    114, 110,  97, 108,  92,  68, 
    105, 114, 101,  99, 116,  88, 
     84,  75,  92,  83, 114,  99, 
     92,  83, 104,  97, 100, 101, 
    114, 115,  92,  76, 105, 103, 
    104, 116, 105, 110, 103,  46, 
    102, 120, 104,   0,  67,  58, 
     92,  85, 115, 101, 114, 115, 
     92, 104,  97, 110, 115, 104, 
     92,  68, 111, 119, 110, 108, 
    111,  97, 100, 115,  92,  50, 
     48,  50,  51,  48,  55,  50, 
     53,  50,  50,  51,  50,  53, 
     49,  95,  67, 111, 100, 101, 
     92,  67, 111, 100, 101,  92, 
     88,  92,  69, 120, 116, 101, 
    114, 110,  97, 108,  92,  68, 
    105, 114, 101,  99, 116,  88, 
     84,  75,  92,  83, 114,  99, 
     92,  83, 104,  97, 100, 101, 
    114, 115,  92,  66,  97, 115, 
    105,  99,  69, 102, 102, 101, 
     99, 116,  46, 102, 120,   0, 
     67,  58,  92,  85, 115, 101, 
    114, 115,  92, 104,  97, 110, 
    115, 104,  92,  68, 111, 119, 
    110, 108, 111,  97, 100, 115, 
     92,  50,  48,  50,  51,  48, 
     55,  50,  53,  50,  50,  51, 
     50,  53,  49,  95,  67, 111, 
    100, 101,  92,  67, 111, 100, 
    101,  92,  88,  92,  69, 120, 
    116, 101, 114, 110,  97, 108, 
     92,  68, 105, 114, 101,  99, 
    116,  88,  84,  75,  92,  83, 
    114,  99,  92,  83, 104,  97, 
    100, 101, 114, 115,  92,  67, 
    111, 109, 109, 111, 110,  46, 
    102, 120, 104,   0,  40,   0, 
      0,   0, 136,   0,   0,   0, 
    234,   0,   0,   0,   0,   0, 
    255, 255,  48,   7,   0,   0, 
      0,   0, 255, 255,  72,   7, 
      0,   0,   0,   0, 255, 255, 
     84,   7,   0,   0,   0,   0, 
    255, 255,  96,   7,   0,   0, 
      0,   0, 255, 255, 108,   7, 
      0,   0,  54,   0,   0,   0, 
    120,   7,   0,   0,  54,   0, 
      0,   0, 136,   7,   0,   0, 
     54,   0,   0,   0, 152,   7, 
      0,   0,  55,   0,   0,   0, 
    168,   7,   0,   0,  55,   0, 
      0,   0, 184,   7,   0,   0, 
     30,   0,   0,   0, 196,   7, 
      0,   0,  30,   0,   0,   0, 
    212,   7,   0,   0,  56,   0, 
      0,   0, 224,   7,   0,   0, 
     56,   0,   0,   0, 240,   7, 
      0,   0,  56,   0,   0,   0, 
      0,   8,   0,   0,  56,   0, 
      0,   0,  16,   8,   0,   0, 
     34,   0,   0,   0,  28,   8, 
      0,   0,  33,   0,   0,   0, 
     44,   8,   0,   0,  39,   0, 
      0,   0,  60,   8,   0,   0, 
     36,   0,   0,   0,  76,   8, 
      0,   0,  39,   0,   0,   0, 
     92,   8,   0,   0,  38,   0, 
      0,   0, 108,   8,   0,   0, 
     43,   0,   0,   0, 124,   8, 
      0,   0,  43,   0,   0,   0, 
    140,   8,   0,   0,  43,   0, 
      0,   0, 152,   8,   0,   0, 
     92,   1,   1,   0, 172,   8, 
      0,   0,  39,   0,   0,   0, 
    188,   8,   0,   0,  39,   0, 
      0,   0, 204,   8,   0,   0, 
     44,   0,   0,   0, 220,   8, 
      0,   0,  44,   0,   0,   0, 
    236,   8,   0,   0,  60,   0, 
      0,   0, 252,   8,   0,   0, 
     11,   0,   2,   0,  12,   9, 
      0,   0,  11,   0,   2,   0, 
     28,   9,   0,   0,  11,   0, 
      2,   0,  44,   9,   0,   0, 
     92,   1,   1,   0,  60,   9, 
      0,   0,  60,   0,   0,   0, 
     76,   9,   0,   0,  60,   0, 
      0,   0,  92,   9,   0,   0, 
     60,   0,   0,   0, 108,   9, 
      0,   0,  84,   1,   1,   0, 
    124,   9,   0,   0,  84,   1, 
      1,   0, 144,   9,   0,   0, 
     91,   1,   1,   0, 156,   9, 
      0,   0,  80,  97, 114,  97, 
    109, 101, 116, 101, 114, 115, 
      0,  68, 105, 102, 102, 117, 
    115, 101,  67, 111, 108, 111, 
    114,   0,   1,   0,   3,   0, 
      1,   0,   4,   0,   1,   0, 
      0,   0,   0,   0,   0,   0, 
     23,   0,   0,   0,   0,   0, 
      1,   0,   2,   0, 255, 255, 
     86,  83,  66,  97, 115, 105, 
     99,  79, 110, 101,  76, 105, 
    103, 104, 116,  84, 120,  86, 
     99,   0,  68, 105, 102, 102, 
    117, 115, 101,   0,   1,   0, 
      3,   0,   1,   0,   4,   0, 
      1,   0,   0,   0,   0,   0, 
      0,   0,  83, 112, 101,  99, 
    117, 108,  97, 114,   0,  84, 
    101, 120,  67, 111, 111, 114, 
    100,   0, 171, 171,   1,   0, 
      3,   0,   1,   0,   2,   0, 
      1,   0,   0,   0,   0,   0, 
      0,   0,  80, 111, 115, 105, 
    116, 105, 111, 110,  80,  83, 
      0, 171, 228,   2,   0,   0, 
    236,   2,   0,   0, 252,   2, 
      0,   0, 236,   2,   0,   0, 
      5,   3,   0,   0,  16,   3, 
      0,   0,  32,   3,   0,   0, 
    236,   2,   0,   0,   5,   0, 
      0,   0,   1,   0,  14,   0, 
      1,   0,   4,   0,  44,   3, 
      0,   0,  25,   0,   0,   0, 
      0,   0,   1,   0,   2,   0, 
    255, 255,  29,   0,   0,   0, 
      4,   0,   5,   0,   6,   0, 
    255, 255,  30,   0,   0,   0, 
    255, 255, 255, 255,  12,   0, 
    255, 255,  33,   0,   0,   0, 
    255, 255, 255, 255, 255, 255, 
      7,   0,  34,   0,   0,   0, 
    255, 255, 255, 255, 255, 255, 
      3,   0,  38,   0,   0,   0, 
     10,   0,  11,   0, 255, 255, 
    255, 255,  39,   0,   0,   0, 
    255, 255, 255, 255, 255, 255, 
     13,   0,  40,   0,   0,   0, 
      8,   0,   9,   0, 255, 255, 
    255, 255, 100, 105, 102, 102, 
    117, 115, 101,   0,   1,   0, 
      3,   0,   1,   0,   3,   0, 
      1,   0,   0,   0,   0,   0, 
      0,   0,  21,   0,   0,   0, 
    255, 255, 255, 255,   0,   0, 
    255, 255, 100, 111, 116,  72, 
      0, 171, 171, 171,  16,   0, 
      0,   0,   0,   0, 255, 255, 
    255, 255, 255, 255, 100, 111, 
    116,  76,   0, 171, 171, 171, 
     17,   0,   0,   0, 255, 255, 
      0,   0, 255, 255, 255, 255, 
    101, 121, 101,  86, 101,  99, 
    116, 111, 114,   0, 171, 171, 
      9,   0,   0,   0,   0,   0, 
      1,   0,   2,   0, 255, 255, 
    104,  97, 108, 102,  86, 101, 
     99, 116, 111, 114, 115,   0, 
      3,   0,   3,   0,   3,   0, 
      3,   0,   1,   0,   0,   0, 
      0,   0,   0,   0,  11,   0, 
      0,   0,   0,   0,   1,   0, 
      2,   0, 255, 255, 112, 111, 
    115,  95, 119, 115,   0, 171, 
      5,   0,   0,   0,   0,   0, 
    255, 255, 255, 255, 255, 255, 
      6,   0,   0,   0, 255, 255, 
      1,   0, 255, 255, 255, 255, 
      7,   0,   0,   0, 255, 255, 
    255, 255,   2,   0, 255, 255, 
    114, 101, 115, 117, 108, 116, 
      0, 171, 228,   2,   0,   0, 
    196,   3,   0,   0, 252,   2, 
      0,   0, 196,   3,   0,   0, 
      5,   0,   0,   0,   1,   0, 
      6,   0,   1,   0,   2,   0, 
    124,   4,   0,   0,  24,   0, 
      0,   0,   0,   0,   1,   0, 
      2,   0, 255, 255, 115, 112, 
    101,  99, 117, 108,  97, 114, 
      0, 171, 171, 171,  27,   0, 
      0,   0,   0,   0, 255, 255, 
    255, 255, 255, 255, 118, 105, 
    110,   0,  80, 111, 115, 105, 
    116, 105, 111, 110,   0,  78, 
    111, 114, 109,  97, 108,   0, 
     67, 111, 108, 111, 114,   0, 
    171, 171, 196,   4,   0,   0, 
    236,   2,   0,   0, 205,   4, 
      0,   0, 196,   3,   0,   0, 
      5,   3,   0,   0,  16,   3, 
      0,   0, 212,   4,   0,   0, 
    236,   2,   0,   0,   5,   0, 
      0,   0,   1,   0,  13,   0, 
      1,   0,   4,   0, 220,   4, 
      0,   0,   1,   0,   0,   0, 
      0,   0,   1,   0,   2,   0, 
      3,   0,   2,   0,   0,   0, 
      4,   0,   5,   0,   6,   0, 
    255, 255,   3,   0,   0,   0, 
      7,   0,   8,   0, 255, 255, 
    255, 255,   4,   0,   0,   0, 
      9,   0,  10,   0,  11,   0, 
     12,   0, 118, 111, 117, 116, 
      0,  80, 111, 115,  95, 112, 
    115,   0,  70, 111, 103,  70, 
     97,  99, 116, 111, 114,   0, 
    171, 171,   0,   0,   3,   0, 
      1,   0,   1,   0,   1,   0, 
      0,   0,   0,   0,   0,   0, 
     65,   5,   0,   0, 236,   2, 
      0,   0, 228,   2,   0,   0, 
    236,   2,   0,   0, 252,   2, 
      0,   0, 196,   3,   0,   0, 
     72,   5,   0,   0,  84,   5, 
      0,   0,   5,   0,   0,   0, 
      1,   0,  12,   0,   1,   0, 
      4,   0, 100,   5,   0,   0, 
     35,   0,   0,   0,   0,   0, 
    255, 255, 255, 255, 255, 255, 
     36,   0,   0,   0, 255, 255, 
      1,   0, 255, 255, 255, 255, 
     37,   0,   0,   0, 255, 255, 
    255, 255,   3,   0, 255, 255, 
    119, 111, 114, 108, 100,  78, 
    111, 114, 109,  97, 108,   0, 
     15,   0,   0,   0,   0,   0, 
      1,   0,   2,   0, 255, 255, 
    122, 101, 114, 111,  76,   0, 
    171, 171,  19,   0,   0,   0, 
    255, 255, 255, 255,   0,   0, 
    255, 255, 156,   2,   0,   0, 
    167,   2,   0,   0, 180,   2, 
      0,   0,   1,   0,   0,   0, 
    196,   2,   0,   0,   0,   0, 
      0,   0, 208,   2,   0,   0, 
     76,   3,   0,   0,   8,   0, 
      0,   0,  92,   3,   0,   0, 
      0,   0,   0,   0, 188,   3, 
      0,   0, 196,   3,   0,   0, 
      1,   0,   0,   0, 212,   3, 
      0,   0,   0,   0,   0,   0, 
    224,   3,   0,   0, 196,   3, 
      0,   0,   1,   0,   0,   0, 
    232,   3,   0,   0,   0,   0, 
      0,   0, 244,   3,   0,   0, 
    196,   3,   0,   0,   1,   0, 
      0,   0, 252,   3,   0,   0, 
      0,   0,   0,   0,   8,   4, 
      0,   0, 196,   3,   0,   0, 
      1,   0,   0,   0,  20,   4, 
      0,   0,   0,   0,   0,   0, 
     32,   4,   0,   0,  44,   4, 
      0,   0,   1,   0,   0,   0, 
     60,   4,   0,   0,   0,   0, 
      0,   0,  72,   4,   0,   0, 
    236,   2,   0,   0,   3,   0, 
      0,   0,  80,   4,   0,   0, 
      0,   0,   0,   0, 116,   4, 
      0,   0, 140,   4,   0,   0, 
      1,   0,   0,   0, 156,   4, 
      0,   0,   0,   0,   0,   0, 
    168,   4,   0,   0, 196,   3, 
      0,   0,   1,   0,   0,   0, 
    180,   4,   0,   0, 208,   2, 
      0,   0, 192,   4,   0,   0, 
    252,   4,   0,   0,   4,   0, 
      0,   0,  12,   5,   0,   0, 
      0,   0,   0,   0,  60,   5, 
      0,   0, 132,   5,   0,   0, 
      3,   0,   0,   0, 148,   5, 
      0,   0,   0,   0,   0,   0, 
    184,   5,   0,   0, 196,   3, 
      0,   0,   1,   0,   0,   0, 
    196,   5,   0,   0,   0,   0, 
      0,   0, 208,   5,   0,   0, 
    196,   3,   0,   0,   1,   0, 
      0,   0, 216,   5,   0,   0, 
     77, 105,  99, 114, 111, 115, 
    111, 102, 116,  32,  40,  82, 
     41,  32,  72,  76,  83,  76, 
     32,  83, 104,  97, 100, 101, 
    114,  32,  67, 111, 109, 112, 
    105, 108, 101, 114,  32,  49, 
     48,  46,  49,   0,  81,   0, 
      0,   5,  19,   0,  15, 160, 
      0,   0,   0,   0,   0,   0, 
    128,  63,   0,   0,   0,   0, 
      0,   0,   0,   0,  31,   0, 
      0,   2,   5,   0,   0, 128, 
      0,   0,  15, 144,  31,   0, 
      0,   2,   5,   0,   1, 128, 
      1,   0,  15, 144,  31,   0, 
      0,   2,   5,   0,   2, 128, 
      2,   0,  15, 144,  31,   0, 
      0,   2,   5,   0,   3, 128, 
      3,   0,  15, 144,   9,   0, 
      0,   3,   0,   0,   1, 128, 
      0,   0, 228, 144,   9,   0, 
    228, 160,   9,   0,   0,   3, 
      0,   0,   2, 128,   0,   0, 
    228, 144,  10,   0, 228, 160, 
      9,   0,   0,   3,   0,   0, 
      4, 128,   0,   0, 228, 144, 
     11,   0, 228, 160,   2,   0, 
      0,   3,   0,   0,   7, 128, 
      0,   0, 228, 129,   7,   0, 
    228, 160,  36,   0,   0,   2, 
      1,   0,   7, 128,   0,   0, 
    228, 128,   2,   0,   0,   3, 
      0,   0,   7, 128,   1,   0, 
    228, 128,   4,   0, 228, 161, 
     36,   0,   0,   2,   1,   0, 
      7, 128,   0,   0, 228, 128, 
      8,   0,   0,   3,   0,   0, 
      1, 128,   1,   0, 228, 144, 
     12,   0, 228, 160,   8,   0, 
      0,   3,   0,   0,   2, 128, 
      1,   0, 228, 144,  13,   0, 
    228, 160,   8,   0,   0,   3, 
      0,   0,   4, 128,   1,   0, 
    228, 144,  14,   0, 228, 160, 
     36,   0,   0,   2,   2,   0, 
      7, 128,   0,   0, 228, 128, 
      8,   0,   0,   3,   0,   0, 
      1, 128,   1,   0, 228, 128, 
      2,   0, 228, 128,   8,   0, 
      0,   3,   0,   0,   2, 128, 
      4,   0, 228, 161,   2,   0, 
    228, 128,  11,   0,   0,   3, 
      0,   0,   1, 128,   0,   0, 
      0, 128,  19,   0,   0, 160, 
     13,   0,   0,   3,   0,   0, 
      4, 128,   0,   0,  85, 128, 
     19,   0,   0, 160,   5,   0, 
      0,   3,   0,   0,   1, 128, 
      0,   0, 170, 128,   0,   0, 
      0, 128,   5,   0,   0,   3, 
      0,   0,   4, 128,   0,   0, 
     85, 128,   0,   0, 170, 128, 
      5,   0,   0,   3,   1,   0, 
      7, 128,   0,   0, 170, 128, 
      5,   0, 228, 160,   1,   0, 
      0,   2,   2,   0,   7, 128, 
      1,   0, 228, 160,   4,   0, 
      0,   4,   1,   0,   7, 128, 
      1,   0, 228, 128,   2,   0, 
    228, 128,   2,   0, 228, 160, 
      5,   0,   0,   3,   0,   0, 
      7, 224,   1,   0, 228, 128, 
      3,   0, 228, 144,  32,   0, 
      0,   3,   1,   0,   1, 128, 
      0,   0,   0, 128,   3,   0, 
    255, 160,   5,   0,   0,   3, 
      0,   0,   1, 128,   0,   0, 
     85, 128,   1,   0,   0, 128, 
      5,   0,   0,   3,   0,   0, 
      7, 128,   0,   0,   0, 128, 
      6,   0, 228, 160,   5,   0, 
      0,   3,   1,   0,   7, 224, 
      0,   0, 228, 128,   3,   0, 
    228, 160,   9,   0,   0,   3, 
      0,   0,   4, 192,   0,   0, 
    228, 144,  17,   0, 228, 160, 
      9,   0,   0,   3,   0,   0, 
      1, 128,   0,   0, 228, 144, 
      8,   0, 228, 160,  11,   0, 
      0,   3,   0,   0,   1, 128, 
      0,   0,   0, 128,  19,   0, 
      0, 160,  10,   0,   0,   3, 
      1,   0,   8, 224,   0,   0, 
      0, 128,  19,   0,  85, 160, 
      5,   0,   0,   3,   0,   0, 
      8, 224,   3,   0, 255, 144, 
      1,   0, 255, 160,   9,   0, 
      0,   3,   0,   0,   1, 128, 
      0,   0, 228, 144,  15,   0, 
    228, 160,   9,   0,   0,   3, 
      0,   0,   2, 128,   0,   0, 
    228, 144,  16,   0, 228, 160, 
      9,   0,   0,   3,   0,   0, 
      4, 128,   0,   0, 228, 144, 
     18,   0, 228, 160,   4,   0, 
      0,   4,   0,   0,   3, 192, 
      0,   0, 170, 128,   0,   0, 
    228, 160,   0,   0, 228, 128, 
      1,   0,   0,   2,   0,   0, 
      8, 192,   0,   0, 170, 128, 
      1,   0,   0,   2,   2,   0, 
      3, 224,   2,   0, 228, 144, 
    255, 255,   0,   0,  83,  72, 
     68,  82,  12,   5,   0,   0, 
     64,   0,   1,   0,  67,   1, 
      0,   0,  89,   0,   0,   4, 
     70, 142,  32,   0,   0,   0, 
      0,   0,  26,   0,   0,   0, 
     95,   0,   0,   3, 242,  16, 
     16,   0,   0,   0,   0,   0, 
     95,   0,   0,   3, 114,  16, 
     16,   0,   1,   0,   0,   0, 
     95,   0,   0,   3,  50,  16, 
     16,   0,   2,   0,   0,   0, 
     95,   0,   0,   3, 242,  16, 
     16,   0,   3,   0,   0,   0, 
    101,   0,   0,   3, 242,  32, 
     16,   0,   0,   0,   0,   0, 
    101,   0,   0,   3, 242,  32, 
     16,   0,   1,   0,   0,   0, 
    101,   0,   0,   3,  50,  32, 
     16,   0,   2,   0,   0,   0, 
    103,   0,   0,   4, 242,  32, 
     16,   0,   3,   0,   0,   0, 
      1,   0,   0,   0, 104,   0, 
      0,   2,   3,   0,   0,   0, 
     16,   0,   0,   8,  18,   0, 
     16,   0,   0,   0,   0,   0, 
     70,  18,  16,   0,   1,   0, 
      0,   0,  70, 130,  32,   0, 
      0,   0,   0,   0,  19,   0, 
      0,   0,  16,   0,   0,   8, 
     34,   0,  16,   0,   0,   0, 
      0,   0,  70,  18,  16,   0, 
      1,   0,   0,   0,  70, 130, 
     32,   0,   0,   0,   0,   0, 
     20,   0,   0,   0,  16,   0, 
      0,   8,  66,   0,  16,   0, 
      0,   0,   0,   0,  70,  18, 
     16,   0,   1,   0,   0,   0, 
     70, 130,  32,   0,   0,   0, 
      0,   0,  21,   0,   0,   0, 
     16,   0,   0,   7, 130,   0, 
     16,   0,   0,   0,   0,   0, 
     70,   2,  16,   0,   0,   0, 
      0,   0,  70,   2,  16,   0, 
      0,   0,   0,   0,  68,   0, 
      0,   5, 130,   0,  16,   0, 
      0,   0,   0,   0,  58,   0, 
     16,   0,   0,   0,   0,   0, 
     56,   0,   0,   7, 114,   0, 
     16,   0,   0,   0,   0,   0, 
    246,  15,  16,   0,   0,   0, 
      0,   0,  70,   2,  16,   0, 
      0,   0,   0,   0,  16,   0, 
      0,   9, 130,   0,  16,   0, 
      0,   0,   0,   0,  70, 130, 
     32, 128,  65,   0,   0,   0, 
      0,   0,   0,   0,   3,   0, 
      0,   0,  70,   2,  16,   0, 
      0,   0,   0,   0,  29,   0, 
      0,   7,  18,   0,  16,   0, 
      1,   0,   0,   0,  58,   0, 
     16,   0,   0,   0,   0,   0, 
      1,  64,   0,   0,   0,   0, 
      0,   0,   1,   0,   0,   7, 
     18,   0,  16,   0,   1,   0, 
      0,   0,  10,   0,  16,   0, 
      1,   0,   0,   0,   1,  64, 
      0,   0,   0,   0, 128,  63, 
     56,   0,   0,   7,  34,   0, 
     16,   0,   1,   0,   0,   0, 
     58,   0,  16,   0,   0,   0, 
      0,   0,  10,   0,  16,   0, 
      1,   0,   0,   0,  56,   0, 
      0,   8, 226,   0,  16,   0, 
      1,   0,   0,   0,  86,   5, 
     16,   0,   1,   0,   0,   0, 
      6, 137,  32,   0,   0,   0, 
      0,   0,   6,   0,   0,   0, 
     50,   0,   0,  11, 226,   0, 
     16,   0,   1,   0,   0,   0, 
     86,  14,  16,   0,   1,   0, 
      0,   0,   6, 137,  32,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   6, 137,  32,   0, 
      0,   0,   0,   0,   1,   0, 
      0,   0,  56,   0,   0,   7, 
    114,  32,  16,   0,   0,   0, 
      0,   0, 150,   7,  16,   0, 
      1,   0,   0,   0,  70,  18, 
     16,   0,   3,   0,   0,   0, 
     56,   0,   0,   8, 130,  32, 
     16,   0,   0,   0,   0,   0, 
     58,  16,  16,   0,   3,   0, 
      0,   0,  58, 128,  32,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,  17,   0,   0,   8, 
     18,   0,  16,   0,   2,   0, 
      0,   0,  70,  30,  16,   0, 
      0,   0,   0,   0,  70, 142, 
     32,   0,   0,   0,   0,   0, 
     15,   0,   0,   0,  17,   0, 
      0,   8,  34,   0,  16,   0, 
      2,   0,   0,   0,  70,  30, 
     16,   0,   0,   0,   0,   0, 
     70, 142,  32,   0,   0,   0, 
      0,   0,  16,   0,   0,   0, 
     17,   0,   0,   8,  66,   0, 
     16,   0,   2,   0,   0,   0, 
     70,  30,  16,   0,   0,   0, 
      0,   0,  70, 142,  32,   0, 
      0,   0,   0,   0,  17,   0, 
      0,   0,   0,   0,   0,   9, 
    226,   0,  16,   0,   1,   0, 
      0,   0,   6,   9,  16, 128, 
     65,   0,   0,   0,   2,   0, 
      0,   0,   6, 137,  32,   0, 
      0,   0,   0,   0,  12,   0, 
      0,   0,  16,   0,   0,   7, 
     18,   0,  16,   0,   2,   0, 
      0,   0, 150,   7,  16,   0, 
      1,   0,   0,   0, 150,   7, 
     16,   0,   1,   0,   0,   0, 
     68,   0,   0,   5,  18,   0, 
     16,   0,   2,   0,   0,   0, 
     10,   0,  16,   0,   2,   0, 
      0,   0,  50,   0,   0,  11, 
    226,   0,  16,   0,   1,   0, 
      0,   0,  86,  14,  16,   0, 
      1,   0,   0,   0,   6,   0, 
     16,   0,   2,   0,   0,   0, 
      6, 137,  32, 128,  65,   0, 
      0,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,  16,   0, 
      0,   7,  18,   0,  16,   0, 
      2,   0,   0,   0, 150,   7, 
     16,   0,   1,   0,   0,   0, 
    150,   7,  16,   0,   1,   0, 
      0,   0,  68,   0,   0,   5, 
     18,   0,  16,   0,   2,   0, 
      0,   0,  10,   0,  16,   0, 
      2,   0,   0,   0,  56,   0, 
      0,   7, 226,   0,  16,   0, 
      1,   0,   0,   0,  86,  14, 
     16,   0,   1,   0,   0,   0, 
      6,   0,  16,   0,   2,   0, 
      0,   0,  16,   0,   0,   7, 
     18,   0,  16,   0,   0,   0, 
      0,   0, 150,   7,  16,   0, 
      1,   0,   0,   0,  70,   2, 
     16,   0,   0,   0,   0,   0, 
     52,   0,   0,   7,  18,   0, 
     16,   0,   0,   0,   0,   0, 
     10,   0,  16,   0,   0,   0, 
      0,   0,   1,  64,   0,   0, 
      0,   0,   0,   0,  56,   0, 
      0,   7,  18,   0,  16,   0, 
      0,   0,   0,   0,  10,   0, 
     16,   0,   1,   0,   0,   0, 
     10,   0,  16,   0,   0,   0, 
      0,   0,  47,   0,   0,   5, 
     18,   0,  16,   0,   0,   0, 
      0,   0,  10,   0,  16,   0, 
      0,   0,   0,   0,  56,   0, 
      0,   8,  18,   0,  16,   0, 
      0,   0,   0,   0,  10,   0, 
     16,   0,   0,   0,   0,   0, 
     58, 128,  32,   0,   0,   0, 
      0,   0,   2,   0,   0,   0, 
     25,   0,   0,   5,  18,   0, 
     16,   0,   0,   0,   0,   0, 
     10,   0,  16,   0,   0,   0, 
      0,   0,  56,   0,   0,   7, 
     18,   0,  16,   0,   0,   0, 
      0,   0,  58,   0,  16,   0, 
      0,   0,   0,   0,  10,   0, 
     16,   0,   0,   0,   0,   0, 
     56,   0,   0,   8, 114,   0, 
     16,   0,   0,   0,   0,   0, 
      6,   0,  16,   0,   0,   0, 
      0,   0,  70, 130,  32,   0, 
      0,   0,   0,   0,   9,   0, 
      0,   0,  56,   0,   0,   8, 
    114,  32,  16,   0,   1,   0, 
      0,   0,  70,   2,  16,   0, 
      0,   0,   0,   0,  70, 130, 
     32,   0,   0,   0,   0,   0, 
      2,   0,   0,   0,  17,  32, 
      0,   8, 130,  32,  16,   0, 
      1,   0,   0,   0,  70,  30, 
     16,   0,   0,   0,   0,   0, 
     70, 142,  32,   0,   0,   0, 
      0,   0,  14,   0,   0,   0, 
     54,   0,   0,   5,  50,  32, 
     16,   0,   2,   0,   0,   0, 
     70,  16,  16,   0,   2,   0, 
      0,   0,  17,   0,   0,   8, 
     18,  32,  16,   0,   3,   0, 
      0,   0,  70,  30,  16,   0, 
      0,   0,   0,   0,  70, 142, 
     32,   0,   0,   0,   0,   0, 
     22,   0,   0,   0,  17,   0, 
      0,   8,  34,  32,  16,   0, 
      3,   0,   0,   0,  70,  30, 
     16,   0,   0,   0,   0,   0, 
     70, 142,  32,   0,   0,   0, 
      0,   0,  23,   0,   0,   0, 
     17,   0,   0,   8,  66,  32, 
     16,   0,   3,   0,   0,   0, 
     70,  30,  16,   0,   0,   0, 
      0,   0,  70, 142,  32,   0, 
      0,   0,   0,   0,  24,   0, 
      0,   0,  17,   0,   0,   8, 
    130,  32,  16,   0,   3,   0, 
      0,   0,  70,  30,  16,   0, 
      0,   0,   0,   0,  70, 142, 
     32,   0,   0,   0,   0,   0, 
     25,   0,   0,   0,  62,   0, 
      0,   1,  73,  83,  71,  78, 
    140,   0,   0,   0,   4,   0, 
      0,   0,   8,   0,   0,   0, 
    104,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,   0,   0, 
      0,   0,  15,  15,   0,   0, 
    116,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,   1,   0, 
      0,   0,   7,   7,   0,   0, 
    123,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,   2,   0, 
      0,   0,   3,   3,   0,   0, 
    132,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      3,   0,   0,   0,   3,   0, 
      0,   0,  15,  15,   0,   0, 
     83,  86,  95,  80, 111, 115, 
    105, 116, 105, 111, 110,   0, 
     78,  79,  82,  77,  65,  76, 
      0,  84,  69,  88,  67,  79, 
     79,  82,  68,   0,  67,  79, 
     76,  79,  82,   0, 171, 171, 
     79,  83,  71,  78, 132,   0, 
      0,   0,   4,   0,   0,   0, 
      8,   0,   0,   0, 104,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   3,   0, 
      0,   0,   0,   0,   0,   0, 
     15,   0,   0,   0, 104,   0, 
      0,   0,   1,   0,   0,   0, 
      0,   0,   0,   0,   3,   0, 
      0,   0,   1,   0,   0,   0, 
     15,   0,   0,   0, 110,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   3,   0, 
      0,   0,   2,   0,   0,   0, 
      3,  12,   0,   0, 119,   0, 
      0,   0,   0,   0,   0,   0, 
      1,   0,   0,   0,   3,   0, 
      0,   0,   3,   0,   0,   0, 
     15,   0,   0,   0,  67,  79, 
     76,  79,  82,   0,  84,  69, 
     88,  67,  79,  79,  82,  68, 
      0,  83,  86,  95,  80, 111, 
    115, 105, 116, 105, 111, 110, 
      0, 171
};