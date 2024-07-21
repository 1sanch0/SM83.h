# From: https://gist.github.com/upsilun/4a85ab3bc7cf92e8acde720c6eb7ddea

class Style:
  RESET_ALL = "\033[0m"
  BOLD = "\033[1m"
  FAINT = "\033[2m"
  ITALIC = "\033[3m"
  UNDERLINE = "\033[4m"
  SLOW_BLINK = "\033[5m"
  RAPID_BLINK = "\033[6m"
  REVERSE_VIDEO = "\033[7m"
  CONCEAL = "\033[8m"
  CROSSED_OUT = "\033[9m"
  # TODO: Styles off

class Text:
  BLACK = "\033[30m"
  RED = "\033[31m"
  GREEN = "\033[32m"
  YELLOW = "\033[33m"
  BLUE = "\033[34m"
  MAGENTA = "\033[35m"
  CYAN = "\033[36m"
  WHITE = "\033[37m"
  DEFAULT = "\033[39m"

class Back:
  BLACK = "\033[40m"
  RED = "\033[41m"
  GREEN = "\033[42m"
  YELLOW = "\033[43m"
  BLUE = "\033[44m"
  MAGENTA = "\033[45m"
  CYAN = "\033[46m"
  WHITE = "\033[47m"
  DEFAULT = "\033[49m"
