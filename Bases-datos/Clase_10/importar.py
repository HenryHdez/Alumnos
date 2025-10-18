import pandas as pd
df = pd.read_csv('datos.csv')
print(df)


df.to_csv('datos2.csv', sep=',' , index=False, header=True)
