typedef enum { True, False } Boolean;

Boolean composeWeights(int weights[], int weightsSize, int newWeight) {
  int index = weightsSize - 1;
  Boolean withLeft, withRight, without;
  if (newWeight == 0) return True;
  if (i == -1) return False;
  withLeft = composeWeights(
    weights,
    weightsSize - 1,
    newWeight - weights[i]
  );
  withRight = composeWeights(
    weights,
    weightsSize - 1,
    newWeight + weights[i]
  );
  without = composeWeights(
    weights,
    weightsSize - 1,
    newWeight
  );
  return withLeft || withRight || without;
}
