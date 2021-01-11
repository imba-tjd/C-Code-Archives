# 本部分代码的特点

* 参数
  * 如果只有一个数组，顺序为arr, len
  * 如果有两个以上数组，顺序为len1, arr1[len1], len2, arr2[len2]
  * 偶尔有C++风格：arr, *end
* 使用了VLA
* 测试用的数组长度是硬编码的10，不打算写sizeof(arr)/sizeof(*arr)
