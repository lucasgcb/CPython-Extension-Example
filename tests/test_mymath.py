from pyextensions import mymath
import pytest

def test_add_error():
    with pytest.raises(TypeError):
        mymath.add('2',[2])

def test_add():
    errMsg = "Add not adding correctly"
    result = mymath.add(2,2)
    assert result == 4, errMsg

def test_xablau():
    errMsg = "System returned non-zero for xablau"
    assert mymath.xablau() == 0, errMsg
