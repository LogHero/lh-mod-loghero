

sudo dnf install cmake httpd-devel
pip install conan
conan install sdk/conan/conanfile.txt --build missing --profile sdk/conan/profiles/linux.cpp
