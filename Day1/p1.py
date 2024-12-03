import time

numbers1 = []
numbers2 = []

for line in open('data.txt').read().split('\n'):
    n1, n2 = line.split()
    numbers1.append(int(n1))
    numbers2.append(int(n2))


numbers1.sort()
numbers2.sort()

t1 = time.time()

for _ in range(10000):

    # dist_sum = 0
    #
    # for i in range(len(numbers1)):
    #     dist_sum += abs(numbers1[i] - numbers2[i])

    dist_sum = sum([abs(a - b) for a, b in zip(numbers1, numbers2)])

    # print(f"Sum of distances: {dist_sum}")

    cut = set(numbers1).intersection(set(numbers2))

    numbers2_dict = {}
    for b in cut:
        numbers2_dict[b] = numbers2_dict.get(b, 0) + 1

    # similarity_score = 0
    #
    # for n in numbers1:
    #     similarity_score += n * numbers2_dict.get(n, 0)

    similarity_score = sum([a * numbers2_dict.get(a, 0) for a in cut])

    # print(f"Similarity score: {similarity_score}")

print(f"Time: {time.time() - t1}")
