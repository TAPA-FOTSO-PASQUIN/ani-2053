#┌──────────────────┐
                     │      NKMath      │   <-- EN HAUT (Construit en 5e / dernier)
                     └────────┬─────────┘
                              │
     ┌───────────────┬────────┴────────┬───────────────┐
     │               │                 │               │
     ▼               ▼                 ▼               ▼
┌──────────┐   ┌──────────┐      ┌──────────┐   ┌──────────┐
│Containers│   │  Memory  │      │   Core   │   │ Platform │
└────┬─────┘   └────┬─────┘      └────┬─────┘   └──────────┘
     │              │                 │
     ├──────────────┼─────────────────┘
     │              │
     ▼              ▼
┌──────────┐   ┌──────────┐
│   Core   │   │ Platform │
└────┬─────┘   └──────────┘
     │
     ▼
┌──────────┐
│ Platform │                                  <-- EN BAS (Construit en 1er)
└──────────┘

Build Order (5 projects):
  1. NKPlatform [STATIC_LIB] → 
  2. NKCore [STATIC_LIB] (depends: NKPlatform) → 
  3. NKMemory [STATIC_LIB] (depends: NKCore, NKPlatform) → 
  4. NKContainers [STATIC_LIB] (depends: NKCore, NKMemory, NKPlatform) → 
  5. NKMath [STATIC_LIB] (depends: NKContainers, NKCore, NKMemory, NKPlatform)
