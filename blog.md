# C++ SSE/AVX を触ってみた

## はじめに

Intelが考案したSSE/AVXという命令セットを利用することで、CPUで実行するコードのSIMD化によって高速化が図れます。   
SSE/AVX命令を利用するようにC++から実際に実装し、どうやってどのくらい高速化できたかなどを備忘録を兼ねて記していきます。   
勉強中ゆえどうしても誤った記述をしてしまうかもしれません。見つけた方はコメントにて教えていただけると大変助かります！

また、この記事は [Aizu Advent Calendar 2019](https://adventar.org/calendars/3938) の5日目の記事です。   
興味がある方は覗いてみてください。     

## 想定読者

- 基本的なC/C++の文法が読める方
- SIMDとかSSEって何？単語だけは耳にしたことあるけど...くらいの方。   
- ごく基本的なCPU周辺のアーキテクチャを知っている方。CPUは演算ユニット、レジスタ、キャッシュがあってRAMと併せて値を読み書きしながら実行して... 程度がわかっていればOK   
  

## 概観の説明

### SISDとSIMD

CPUは実行ファイル(や、アセンブリプログラム)に記述された命令を読み込んで実行します。   
SSE/AVXを利用しない通常の命令セットでは、**1つのデータ**に対して**1つの演算**を行います。つまり[フリンの分類]([https://ja.wikipedia.org/wiki/%E3%83%95%E3%83%AA%E3%83%B3%E3%81%AE%E5%88%86%E9%A1%9E](https://ja.wikipedia.org/wiki/フリンの分類))で言う**SISD**というものです。   
すると、CPUリソースが無駄になってしまうことがあります。例えばこんな感じです。

![image-20191205012928353](C:\Users\albus\AppData\Roaming\Typora\typora-user-images\image-20191205012928353.png)  
この無駄な部分を利用して、本来次のステップで演算される予定だった別のデータに対する演算を**このステップで同時に実行**できるようにする、というのが**SIMD**型演算のアイデアです。    

### SSE/AVX

CPUでのSIMD型演算を可能にしたx86命令セットの拡張が、Intelが考案した[**SSE/AVX**](https://ja.wikipedia.org/wiki/ストリーミングSIMD拡張命令)です。   
それぞれ **Streaming SIMD Extensions**,  **Advanced Vector Extensions**といい、AVXは後に考案されたSSEの後継バージョンです。   
これらはそれぞれ128bitsの**xmm**レジスタ、256bitsの**ymm**レジスタを利用して演算します。   
このレジスタはSIMD演算のためにCPUへ組み込まれた追加のレジスタで、それ意外の用途には使われません。     

### C言語のIntrinsics

プログラマーがCPU命令セットを呼び出すよう記述するには普通アセンブリ言語でプログラムを書く必要がありますが、それをC言語から呼び出せるようにした**組み込み関数**が用意されています。   
これらは**Intrinsics**と呼ばれる関数群です。    
SSE/AVXも同様にIntrinsicとして実行できます。   

### 並列処理とSIMD演算の違い

並列処理は、**1つの処理**をCPUの**複数のスレッドで分担**させて行います。   
対して、SIMD演算は**複数のデータに対する1つの命令**をCPUの**1つのコア内のxmm/ymmレジスタで分担**させて行います。   
![image-20191205012959120](C:\Users\albus\AppData\Roaming\Typora\typora-user-images\image-20191205012959120.png)   

## C++プログラムのSIMD化

お膳立てが済んだところで、C++からのIntrinsics呼び出しによる高速化を試してみます。   
ベンチマークとして、ベクトルの内積、外積、行列演算をやってみました。要旨と関係ない部分のコードは割愛します。   

## 注意点・ハマったところなど

- lord元/store先になるメモリ領域がSSEなら16bytes-aligned, AVXなら32bytes-alignedになっていないとSegmentation Faultでプログラムが落ちる
- std::vectorに突っ込んだ時のサイズはどうなってるか？
  アラインメントの影響ででかくなっているかも

## 分からないところ・疑問

一通り触ってみて、自力で解決できなかったことを挙げます。   
これらを解説する資料や技術書などがあればコメントで教えていただければ嬉しいです！

- xmm/ymmレジスタはCPUの**1コアにつき**1つ存在している？    
- もし ↑ の通りならば、Intrinsicsを含むコードを実行する並列スレッド数(`std::thread`などのインスタンス数)をCPUのコア数より多くすればxmm/ymmレジスタの値が破綻し得る？
- コンパイラの最適化は、可能な部分は勝手にSIMD化してくれるのか？
- SSE/AVXのほかにFMAという命令セット拡張があり、SSE->AVXのようにサイズが増えたわけではないらしい。用途は何だろう？

## おわりに

以上です。

### 参考文献

[Intel AVX を使用して SIMD 演算を試してみる](http://kawa0810.hateblo.jp/entries/2012/03/03)   
[Intel AVX を使用して SIMD 演算を試してみる - その2 -](http://kawa0810.hateblo.jp/entry/20120304/1330852197)   
[Introduction to Intel® Advanced Vector Extensions](https://software.intel.com/en-us/articles/introduction-to-intel-advanced-vector-extensions)   
[組み込み関数（intrinsic）によるSIMD入門](https://www.slideshare.net/FukushimaNorishige/simd-10548373)    
[SIMD - primitive: blog](http://i-saint.hatenablog.com/entry/20101003/1286043166)