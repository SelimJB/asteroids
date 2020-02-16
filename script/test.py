import yaml
import ntpath

with open("./config.yaml", "r") as stream:
	try:
		dataloaded = yaml.load(stream)
	except yaml.YAMLError as exc:
		print(exc)

print ntpath.join(
	dataloaded["neural_network"]["path"],
	dataloaded["neural_network"]["neural_network_name"]+".txt"
)
# #  A ARCHIVER COMME EXEMPLE
# #  COMMENT TRACER UNE REGRESSION
# import matplotlib.pyplot as plt
# import numpy as np
# from sklearn import linear_model

# # regr = linear_model.LinearRegression()
# # regr.fit( [ [x,y] for x,y in zip(range(0,6), [1,2,3,1,4,2])], [1,2,3,1,4,2] )
# # plt.ylabel('some numbers')
# # plt.plot(range(0,6), [1,2,3,1,4,2])
# # print 'slope', regr.coef_
# # print 'intercept', regr.intercept_
# # plt.show()
# # # plt.savefig('books_read.png')

# x = np.array(range(0,5))
# y = np.array([4,2,4,2,4])


# plt.scatter(x,y)

# regr = linear_model.LinearRegression()
# regr.fit(x[:,np.newaxis], y)

# x_test = np.linspace(np.min(x), np.max(x), 100)

# # plt.plot(x_test, regr.predict(x_test[:,np.newaxis]), color='blue', linewidth=1)
# plt.plot(x,y, color='blue', linewidth=1)
# plt.plot(x,np.array([regr.intercept_ + i* regr.coef_ for i in x]), color='red', linewidth=0.5)
# print regr.coef_
# plt.show()

