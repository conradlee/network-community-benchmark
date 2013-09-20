
from sklearn import ensemble

N_FOLDS = 10
MIN_ATTR_INSTANCES = 4

### Folder locations ###

CACHED_TABLES_FOLDER = '/home/conradlee/facebook100-infer/cached/'
SRC_DATA_DIR = '/home/conradlee/Downloads/facebook100/'
HOLDOUT_DIR = '/home/conradlee/facebook100-infer/holdouts/'
BENCHMARK_ROOT = '/home/conradlee/github/network-community-benchmark'

OTHER_CATEGORY_THRESHOLD = 10
ATTRS_DTYPE = [('student_fac', 'u1'),
               ('gender', 'u1'),
               ('first_major', 'u4'),
               ('second_major', 'u4'),
               ('dorm', 'u4'),
               ('year', 'i4'),
               ('high_school', 'u4')]

# Classification settings

CLASSIFIER = ensemble.GradientBoostingClassifier(learning_rate=0.005, n_estimators=1000, min_samples_split=5, subsample=0.4)

MIN_LABEL_FREQ = 10
MIN_FEATURE_FREQ = 4
