#!/usr/bin/env python3

import re
import sys
import base64

import intelhex
from flask import Flask, request


def read_bin(fn):
    ih = intelhex.IntelHex()
    ih.loadhex(fn)
    return ih.tobinstr()


if len(sys.argv) != 2:
    print(f"USAGE: {sys.argv[0]} [IHEX FILE]")
    exit(1)
code_bin = read_bin(sys.argv[1])

app = Flask(__name__)


@app.route("/data", methods=["POST"])
def data():
    pa, buf_lim = map(int, re.match(r"\[(\d+) (\d+)\]", request.data.decode()).groups())
    print(f"Request from {pa} memory address for {buf_lim} bytes. Sending: ")
    enc = base64.b64encode(code_bin[pa : pa + buf_lim])
    print(enc)
    return enc, 200


@app.route("/npages", methods=["POST"])
def npages():
    pagesize = int(request.data[1:-1])
    npages = str((len(code_bin) + pagesize - 1) // pagesize)
    print(f"Request for npages with given pagesize {pagesize}. Sending: {npages}")
    return npages, 200


if "__main__" == __name__:
    app.run("0.0.0.0", debug=True)
