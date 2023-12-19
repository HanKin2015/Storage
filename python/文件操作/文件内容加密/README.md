# 文件加密
自定义加密规则：https://blog.csdn.net/qq_53280175/article/details/121748680

## 1、加密方式
对称加密算法：对称加密算法使用相同的密钥来加密和解密数据。常见的对称加密算法包括AES、DES和3DES。你可以使用Python中的cryptography库或pycryptodome库来实现对称加密算法。

文件压缩加密：你可以先使用文件压缩算法（如ZIP或GZIP）来压缩文件，然后再对压缩后的文件进行加密。这种方法可以同时实现文件的加密和压缩，减小文件大小。

散列函数：散列函数将文件映射为固定长度的哈希值。你可以使用Python中的hashlib库来计算文件的散列值。然后，你可以将散列值保存在安全的地方，并在需要时验证文件的完整性。

混合加密：混合加密是将多种加密算法结合在一起使用。例如，你可以使用RSA算法来加密对称密钥，然后使用对称密钥来加密文件内容。这种方法结合了RSA算法的安全性和对称加密算法的高效性。

请注意，无论使用哪种加密方法，都需要妥善保管密钥和加密算法的安全性，以确保加密和解密的安全性。此外，加密算法的选择应根据具体的安全需求和性能要求进行评估。

## 2、Crypto库和cryptography库区别
Crypto库和cryptography库都是Python中用于加密和密码学操作的库，但它们有一些区别。

1、功能和设计理念:
- Crypto库是由PyCrypto项目提供的，提供了丰富的密码学功能，包括对称加密、非对称加密、数字签名、散列函数等。它的设计比较传统，功能较为全面。
- cryptography库是由PyCA（Python Cryptographic Authority）提供的，它提供了现代密码学算法的实现，包括对称加密、非对称加密、数字签名、密钥派生等。它的设计更加现代化，注重安全性和易用性。

2、支持性:
- Crypto库在一些旧版本的Python中可能存在兼容性问题，而cryptography库则更加现代化，支持Python 3.6及以上的版本。
- cryptography库在设计上更加注重安全性和最佳实践，因此在一些新项目中更受推荐。

3、维护和更新:
- 由于PyCrypto项目已经停止维护，Crypto库也不再活跃更新，而cryptography库是一个活跃维护的项目，因此在长期支持和更新方面更有优势。
总的来说，如果你在新项目中需要使用密码学功能，特别是对现代密码学算法有需求，那么cryptography库可能是一个更好的选择。如果你需要在旧版本的Python中使用密码学功能，或者对传统密码学算法有需求，那么Crypto库可能是一个选择。

## 3、使用pip list没有看见Crypto库，但是能正常导入
对于Crypto库，它实际上是PyCrypto库的一部分，而PyCrypto库在pip list中可能以pycrypto的形式显示。因此，当你使用import Crypto时，实际上是在导入PyCrypto库的功能。
另外，有些库可能是作为其他库的依赖项而安装的，这些库在pip list中可能不会单独显示，而是作为其他库的一部分显示出来。这可能会导致你能够正常导入这些库，但在pip list中找不到对应的名称。
总之，虽然在pip list中找不到某个库的名称，但并不意味着你不能正常导入和使用它。如果你能够成功导入并使用某个库，那么通常意味着该库已经被正确安装并可用。

PyCryptodome是PyCrypto的一个分支，它提供了对PyCrypto的改进和扩展，并且在一些情况下取代了PyCrypto。因此，当你安装PyCryptodome时，它可能会在pip list中以pycryptodome的形式显示。
所以，如果你在pip list中找不到Crypto或PyCrypto，但安装了PyCryptodome，那么你仍然可以使用import Crypto或import Crypto.Something来导入PyCryptodome库的功能。这是因为PyCryptodome在设计上是为了向后兼容PyCrypto，因此它保留了类似的导入方式和接口。

## 4、








