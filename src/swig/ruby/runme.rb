require 'proto'

name = "Frank N. Stein"
name_len = Proto.get_payload_size(name)

print "The name is ", name_len, " characters long\n"
