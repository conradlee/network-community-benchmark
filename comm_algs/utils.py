import tempfile
import shutil
import itertools
import os

class Tempdir:
    def __enter__(self):
        self.dir = tempfile.mkdtemp()
        return self.dir
    def __exit__(self, tye, value, traceback):
        try:
            #print self.dir
            shutil.rmtree(self.dir)
        except OSError:
            pass

class Tempfile:
    def __enter__(self):
        self.file = tempfile.NamedTemporaryFile(delete=False)
        return self.file
    def __exit__(self, type, value, traceback):
        try:
            os.remove(self.file.name)
        except OSError:
            pass

def pairwise(iterable):
    "s -> (s0,s1), (s1,s2), (s2, s3), ..."
    a, b = itertools.tee(iterable)
    next(b, None)
    return itertools.izip(a, b)
