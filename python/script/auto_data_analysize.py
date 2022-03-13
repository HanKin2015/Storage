### Importing Seaborn Library For Some Datasets
import seaborn as sns

### Printing Inbuilt Datasets of Seaborn Library
print(sns.get_dataset_names())


### Loading Titanic Dataset
df=sns.load_dataset('titanic')

### Importing The Library
import dtale

#### Generating Quick Summary
dtale.show(df)