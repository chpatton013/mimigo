solution ('mimigo')
   configurations ({'Debug', 'Release'})
   language ('C++')
   files ({'src/**.cpp', 'src/**.cc', 'src/**.h'})
   defines ({})
   links ({})

   configuration ('Debug')
      defines ({'DEBUG'})
      flags ({'Symbols'})

   configuration ('Release')
      defines ({'NDEBUG'})
      flags ({'Optimize'})

   project ('game')
      kind ('WindowApp')
