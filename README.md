# machine_learning
Clothes Classifaction

With about 10000 pictures of clothes to deal with, for the content, the pictures include wearing pants, jeans, skirts, T-shirts, blouse, ans do on...., for the dimension, it includes different kinds of sizes, in order to tackle all these kinds of pictures, the first part is to reshape all of the pictures into 150*150 dimension,and then divided them into 80% and 20%, the latter is for validation.

With the second part, includes model choosing, parameter adjustment, and prediction, the model use Adam for optimizer, learning rate for 0.0001, and adds L2 normalization with dropout(0.5), ibn order to prevent overfitting, the model add earlystop function, finally, the result shows that the model for public score and private score has about the same validation accuracy, it also demonstrates that the model has better predictive power.



[ml_result.pptx](https://github.com/garyold/machine_learning/files/11712806/ml_result.pptx)
