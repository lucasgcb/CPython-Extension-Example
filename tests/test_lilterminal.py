from pyextensions import lilterminal
import pytest

def test_system():
    errMsg = "System returned non-zero for echo"
    assert lilterminal.system("echo hello") == 0, errMsg

def test_xablau():
    errMsg = "System returned non-zero for xablau"
    assert lilterminal.xablau() == 0, errMsg