# Import libraries
import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.tree import DecisionTreeClassifier
from sklearn.preprocessing import LabelEncoder
from sklearn.metrics import accuracy_score, confusion_matrix, classification_report
import matplotlib.pyplot as plt
from sklearn import tree

# Step 1: Load dataset
df = pd.read_csv("Admission_Predict.csv")

# Step 2: Preprocessing
df.rename(columns={'Chance of Admit ': 'Chance_of_Admit'}, inplace=True)

# Binarize target: If Chance >= 0.5 -> 1 (admitted), else 0 (not admitted)
df['Admitted'] = df['Chance_of_Admit'].apply(lambda x: 1 if x >= 0.5 else 0)

# Select only required features: GRE Score and CGPA
X = df[['GRE Score', 'CGPA']]
y = df['Admitted']

# Step 3: Train-test split
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

# Step 4: Train Decision Tree Classifier
clf = DecisionTreeClassifier(random_state=42)
clf.fit(X_train, y_train)

# Step 5: Predict and evaluate
y_pred = clf.predict(X_test)

# Evaluation
print("Accuracy:", accuracy_score(y_test, y_pred))
print("Confusion Matrix:\n", confusion_matrix(y_test, y_pred))
print("Classification Report:\n", classification_report(y_test, y_pred))

# Step 6: Visualize Decision Tree
plt.figure(figsize=(12,8))
tree.plot_tree(clf, feature_names=['GRE Score', 'CGPA'], class_names=['No', 'Yes'], filled=True)
plt.title("Decision Tree for Admission Prediction")
plt.show()
