# SIMD practice code

SSE/AVX Intrinsicsによる簡単なベクトル/行列演算の時間計測をするコードです。   

### コンパイル/実行

```
$ cd bin
$ make simdexec_noopt # -O0で実行ファイル生成
$ make simdexec_opt3  # -O3で実行ファイル生成
$ ./simdexec_noopt    # 実行ファイル内のベンチマーク対象の関数を100000回(デフォルトの回数)実行
& ./simdexec_opt3 500 # 実行ファイル内のベンチマーク対象の関数を500回実行
```
