from ctypes import *
from pathlib import Path

class SM83Instruction(Structure):
  _fields_ = [('mnemonic', c_char_p),
              ('exec', CFUNCTYPE(None, POINTER('SM83'))),
              ('length', c_uint8),
              ('ticks', c_uint8)]

class SM83(Structure):
  _fields_ = [('af', c_uint16),
              ('bc', c_uint16),
              ('de', c_uint16),
              ('hl', c_uint16),
              ('sp', c_uint16),
              ('pc', c_uint16),
              ('read', CFUNCTYPE(c_uint8, c_uint16)),
              ('write', CFUNCTYPE(None, c_uint16, c_uint8)),
              ('t', c_uint8),
              ('instruction', POINTER(SM83Instruction))]
  
  @property
  def a(self):
    return self.af >> 8
  
  @a.setter
  def a(self, value):
    self.af = (self.af & 0xFF) | (value << 8)
  
  @property
  def f(self):
    return self.af & 0xFF
  
  @f.setter
  def f(self, value):
    self.af = (self.af & 0xFF00) | value
  
  @property
  def b(self):
    return self.bc >> 8
  
  @b.setter
  def b(self, value):
    self.bc = (self.bc & 0xFF) | (value << 8)

  @property
  def c(self):
    return self.bc & 0xFF
  
  @c.setter
  def c(self, value):
    self.bc = (self.bc & 0xFF00) | value

  @property
  def d(self):
    return self.de >> 8
  
  @d.setter
  def d(self, value):
    self.de = (self.de & 0xFF) | (value << 8)

  @property
  def e(self):
    return self.de & 0xFF
  
  @e.setter
  def e(self, value):
    self.de = (self.de & 0xFF00) | value

  @property
  def h(self):
    return self.hl >> 8
  
  @h.setter
  def h(self, value):
    self.hl = (self.hl & 0xFF) | (value << 8)
  
  @property
  def l(self):
    return self.hl & 0xFF
  
  @l.setter
  def l(self, value):
    self.hl = (self.hl & 0xFF00) | value

__lib = CDLL(Path(__file__).parent / 'libsm83.so')

__lib.SM83_init.argtypes = [POINTER(SM83), c_void_p, c_void_p]
__lib.SM83_reset.argtypes = [POINTER(SM83)]
__lib.SM83_tick.argtypes = [POINTER(SM83)]

SM83_init = __lib.SM83_init
SM83_reset = __lib.SM83_reset
SM83_tick = __lib.SM83_tick
