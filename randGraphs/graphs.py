import random
import itertools
from pathlib import Path

# ---------------- Configuration ----------------

NODE_SIZES = {
    "small": 12,
    "medium": 100,
    "big": 1_000
}

DENSITIES = ["sparse", "medium", "dense"]
COPIES_PER_COMBO = 3
BASE_DIR = Path(".")

# ---------------- Graph Generation ----------------

def edge_count(num_nodes, directed, dag, density):
    if directed:
        max_edges = num_nodes * (num_nodes - 1) // 2 if dag else num_nodes * (num_nodes - 1)
    else:
        max_edges = num_nodes * (num_nodes - 1) // 2

    if density == "sparse":
        return min(max_edges, max(num_nodes - 1, num_nodes * 2))
    if density == "medium":
        return max_edges // 2
    return max_edges


def generate_edges(num_nodes, directed, dag, num_edges):
    edges = set()

    while len(edges) < num_edges:
        u = random.randrange(num_nodes)
        v = random.randrange(num_nodes)

        if u == v:
            continue

        if directed:
            if dag and u > v:
                u, v = v, u
            edge = (u, v)
        else:
            edge = tuple(sorted((u, v)))

        edges.add(edge)

    return edges


def generate_graph(
    filepath,
    num_nodes,
    directed,
    weighted,
    allow_negative,
    dag,
    density
):
    num_edges = edge_count(num_nodes, directed, dag, density)
    edges = generate_edges(num_nodes, directed, dag, num_edges)

    with open(filepath, "w") as f:
        f.write(f"{num_nodes} {len(edges)} {1 if directed else 0}\n")

        for u, v in edges:
            if weighted:
                if allow_negative:
                    w = random.choice([i for i in range(-20, 21) if i != 0])
                else:
                    w = random.randint(1, 20)
                f.write(f"{u} {v} {w}\n")
            else:
                f.write(f"{u} {v}\n")


# ---------------- Directory Helpers ----------------

def build_output_dir(directed, weighted, allow_negative, dag):
    parts = [
        "directed" if directed else "undirected",
        "weighted" if weighted else "unweighted",
    ]

    if weighted:
        parts.append("negative" if allow_negative else "positive")

    if directed:
        parts.append("dag" if dag else "cyclic")

    path = BASE_DIR.joinpath(*parts)
    path.mkdir(parents=True, exist_ok=True)
    return path


# ---------------- Main Driver ----------------

def main():
    for size_name, num_nodes in NODE_SIZES.items():
        for directed, weighted in itertools.product([False, True], repeat=2):

            dag_options = [False, True] if directed else [False]
            negative_options = [False, True] if weighted else [False]

            for dag, allow_negative, density in itertools.product(
                dag_options,
                negative_options,
                DENSITIES
            ):
                out_dir = build_output_dir(
                    directed, weighted, allow_negative, dag
                )

                for i in range(1, COPIES_PER_COMBO + 1):
                    filename = f"{size_name}{density.capitalize()}{i}.txt"
                    filepath = out_dir / filename

                    print(f"Generating {filepath}")
                    generate_graph(
                        filepath,
                        num_nodes,
                        directed,
                        weighted,
                        allow_negative,
                        dag,
                        density
                    )


if __name__ == "__main__":
    main()
