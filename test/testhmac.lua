package.cpath = package.cpath .. ";../src/?.so"
local hmac = require "hmac"

local sha256 = hmac.sha256("hl;klljljkljljljkljkljklj", "012345678")
print("msg:hl;klljljkljljljkljkljklj key:012345678")
print(sha256)
