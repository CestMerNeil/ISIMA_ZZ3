import numpy as np

class KMeans:
    def __init__(self, n_clusters, max_iter=1000):
        self.n_clusters = n_clusters
        self.max_iter = max_iter
        self.centroids = None

    def _calculate_distance(self, X, centroids):
        return np.linalg.norm(X[:, np.newaxis] - centroids, axis=2)

    def _initialize_centroids(self, X):
        np.random.seed(42)
        random_indices = np.random.choice(X.shape[0], self.n_clusters, replace=False)
        self.centroids = X[random_indices]

    def fit(self, X):
        self._initialize_centroids(X)

        for _ in range(self.max_iter):
            distances = self._calculate_distance(X, self.centroids)
            labels = np.argmin(distances, axis=1)

            new_centroids = np.array([np.mean(X[labels == i], axis=0) if np.any(labels == i) 
                                      else self.centroids[i] for i in range(self.n_clusters)])

            if np.linalg.norm(new_centroids - self.centroids) < 1e-4:
                break

            self.centroids = new_centroids

    def predict(self, X):
        distances = self._calculate_distance(X, self.centroids)
        return np.argmin(distances, axis=1)