
from sklearn import ensemble

# The location of the facebook100 dataset--i.e., the place you unzipped
# Facebook100.zip
SRC_DATA_DIR = '/home/conradlee/Downloads/facebook100/'

# The path of the github repository, where the benchmarking code
# lives
BENCHMARK_ROOT = '/home/conradlee/github/network-community-benchmark'

# The number of folds of the 10-fold cross validation to
# carry out (max 10)
N_FOLDS = 10           

# If some label value has very few instances, then it is not
# appropriate for this benchmark.  For example, in the 'year' attribute,
# most students have a graduation year between 2002 and 2010, but a few
# people (perhaps alumni or professors) have values such as 1982, etc. Because
# such outliers are so infreqent, we can't expect the classifier to infer them
# based on community structure.  MIN_LABEL_FREQ is a threshold value---if some
# attribute value has fewer than that MIN_LABEL_FREQ instances, then
# those nodes with those values are left out of the classification task.
MIN_LABEL_FREQ = 10

# After forming the community assignment matrix nodes are removed if they
# not have an accepted label (because they have an unknown label or one that's
# below the MIN_LABEL_FREQ threshold).  If after removing these nodes, some
# communities have fewer than MIN_FEATURE_FREQ members, then those columns of the
# community assignment matrix will be removed.
MIN_FEATURE_FREQ = 4

# CLASSIFIER is the classifier used for the classification task.  Any scikit-learn
# classifier can be used.
CLASSIFIER = ensemble.GradientBoostingClassifier(learning_rate=0.005, n_estimators=1000, min_samples_split=5, subsample=0.4)

# The following list indicates the order of the attributes read in from the source
# matlab file, and maps attributes to numpy dtypes.  You should not need to change
# this list.
ATTRS_DTYPE = [('student_fac', 'u1'),
               ('gender', 'u1'),
               ('first_major', 'u4'),
               ('second_major', 'u4'),
               ('dorm', 'u4'),
               ('year', 'i4'),
               ('high_school', 'u4')]



