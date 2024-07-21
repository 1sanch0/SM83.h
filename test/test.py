from sm83 import *
import json
from utils.colors import Style, Text, Back

memory = (c_uint8 * 0x10000)()

@CFUNCTYPE(c_uint8, c_uint16)
def read(addr):
  return memory[addr]

@CFUNCTYPE(None, c_uint16, c_uint8)
def write(addr, value):
  # print(f'Writing {value} to {addr}')
  memory[addr] = value

def zero_memory():
  for i in range(0x10000):
    memory[i] = 0


class Snapshot:
  def __init__(self, state):
    self.cpu = SM83()
    SM83_init(self.cpu, read, write)
    SM83_reset(self.cpu)
    
    self.ram = None

    self._set_state(state)
  
  def run(self):
    zero_memory() # TODO: Ideally memory should be local to the Snapshot class
    for (addr, value) in self.ram:
      memory[addr] = value

    SM83_tick(self.cpu)

    # for i, (addr, _) in enumerate(self.ram):
    #   self.ram[i] = [addr, memory[addr]]
    
  def __eq__(self, value: 'Snapshot') -> bool:
    self.ram = []
    for (addr, _) in value.ram:
      self.ram.append([addr, memory[addr]])

    return isinstance(value, Snapshot) and \
           self.cpu.af == value.cpu.af and \
           self.cpu.bc == value.cpu.bc and \
           self.cpu.de == value.cpu.de and \
           self.cpu.hl == value.cpu.hl and \
           self.cpu.sp == value.cpu.sp and \
           self.cpu.pc == value.cpu.pc and \
           self.ram == value.ram
  
  def __str__(self):
    return f"AF: {self.cpu.af:04X} BC: {self.cpu.bc:04X} DE: {self.cpu.de:04X} HL: {self.cpu.hl:04X} SP: {self.cpu.sp:04X} PC: {self.cpu.pc:04X}"

  def _set_state(self, state):
    self.cpu.a = state['a']
    self.cpu.f = state['f']
    self.cpu.b = state['b']
    self.cpu.c = state['c']
    self.cpu.d = state['d']
    self.cpu.e = state['e']
    self.cpu.h = state['h']
    self.cpu.l = state['l']
    self.cpu.sp = state['sp']
    self.cpu.pc = state['pc']

    self.ram = state['ram']


if __name__ == '__main__':
  cwd = Path(__file__).parent
  test_dir = cwd / 'GameboyCPUTests' / 'v2'

  # EXIT_ON_FAIL = False
  EXIT_ON_FAIL = True

  files = list(test_dir.glob('**/*.json'))
  files.sort(key=lambda x: x.name)

  for test in files:
    print(Style.RESET_ALL + Style.BOLD + Style.ITALIC + Style.UNDERLINE + f"{test}:" + Style.RESET_ALL, end=' ')

    # testing = ['cb']
    # if not (test.stem in testing):
    #   print(Style.RESET_ALL + Style.FAINT + Text.YELLOW + "Skipping" + Style.RESET_ALL)
    #   continue

    failed = False
    for case in json.loads(test.read_text()):
      emulated = Snapshot(case['initial'])

      emulated.cpu.pc -= 1 # TODO
      emulated.run()
      emulated.cpu.pc += 1 # TODO

      ticks = emulated.cpu.t
      cycles = ticks // 4

      # print("PC:", emulated.cpu.pc)
      # print(f"Ran for {ticks} ticks")
      # print(emulated.cpu.instruction.contents.length)
      if (ticks == 255):
        print(Style.RESET_ALL + Style.BOLD + Text.YELLOW + case["name"] + Style.RESET_ALL)
        print(Style.RESET_ALL + Style.BOLD + Text.YELLOW + "Unimplemented opcode" + Style.RESET_ALL)
        failed = True
        break

      expected = Snapshot(case['final'])
      expected_cycles = len(case['cycles'])

      if cycles != expected_cycles:
        print(Style.RESET_ALL + Style.BOLD + Text.RED + case["name"] + Style.RESET_ALL)
        print(Style.RESET_ALL + Style.BOLD + Text.RED + f"Failed timing: {cycles} != {expected_cycles}" + Style.RESET_ALL)
        failed = True
        break

      if emulated != expected:
        print(Style.RESET_ALL + Style.BOLD + Text.RED + case["name"] + Style.RESET_ALL)
        print(Style.RESET_ALL + Style.BOLD + Text.RED + "Failed" + Style.RESET_ALL)

        print("Expected:")
        print(expected)
        print(f"{expected.cpu.f:08b}")
        print(expected.ram)
        print("Emulated:")
        print(emulated)
        print(f"{emulated.cpu.f:08b}")
        print(emulated.ram)

        failed = True
        break

    if not failed:
      print(Style.RESET_ALL + Style.BOLD + Text.GREEN + "Passed" + Style.RESET_ALL)
    else:
      if EXIT_ON_FAIL:
        exit(1)