import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
import ast
import os

sns.set_style('whitegrid')

# --- 1. Data Loading and Cleaning ---

def load_and_clean_data(movies_path, credits_path):
    print("Step 1: Loading and Cleaning Data...")
    try:
        movies_df = pd.read_csv(movies_path)
        credits_df = pd.read_csv(credits_path)
    except FileNotFoundError:
        print(f"Error: Make sure '{movies_path}' and '{credits_path}' are in the same directory.")
        return None

    credits_df.rename(columns={'movie_id': 'id'}, inplace=True)
    df = movies_df.merge(credits_df, on='id')

    # Drop unneeded columns if present
    for col in ['homepage', 'original_title', 'overview', 'status', 'tagline', 'title_y']:
        if col in df.columns:
            df.drop(columns=[col], inplace=True)
    if 'title_x' in df.columns:
        df.rename(columns={'title_x': 'title'}, inplace=True)

    # Replace zeros with NaN for budget/revenue and drop rows missing them
    df['budget'] = df['budget'].replace(0, np.nan)
    df['revenue'] = df['revenue'].replace(0, np.nan)
    df.dropna(subset=['budget', 'revenue'], inplace=True)

    # Fill runtime missing with mean
    if 'runtime' in df.columns:
        df['runtime'] = df['runtime'].fillna(df['runtime'].mean())

    # Convert types
    df['release_date'] = pd.to_datetime(df['release_date'], errors='coerce')

    # Convert to int safely
    df['budget'] = df['budget'].astype('int64')
    df['revenue'] = df['revenue'].astype('int64')

    json_columns = [col for col in ['genres', 'keywords', 'production_companies', 'cast', 'crew'] if col in df.columns]
    for col in json_columns:
        df[col] = df[col].apply(lambda x: ast.literal_eval(x) if isinstance(x, str) else x)

    print("Data Loading and Cleaning Complete.\n")
    return df

# Helpers

def get_names(data_list, key='name'):
    return [item[key] for item in data_list] if isinstance(data_list, list) else []

def get_director(crew_list):
    if not isinstance(crew_list, list):
        return None
    for member in crew_list:
        if member.get('job') == 'Director':
            return member.get('name')
    return None

# --- EDA ---

def exploratory_data_analysis(df):
    print("Step 2 & 3: Performing Exploratory Data Analysis...")

    # Genre analysis
    genre_df = df.copy()
    genre_df['genres'] = genre_df['genres'].apply(get_names)
    genre_df = genre_df.explode('genres')

    plt.figure(figsize=(10, 6))
    sns.countplot(y='genres', data=genre_df, order=genre_df['genres'].value_counts().index, palette='mako')
    plt.title('Number of Movies by Genre')
    plt.tight_layout()
    plt.savefig('movies_by_genre.png')
    print("Chart saved: 'movies_by_genre.png'")
    plt.show()

    # Highest rated in top 5 genres
    top_genres = genre_df['genres'].value_counts().nlargest(5).index
    print("\n--- Highest Rated Movie in Top Genres ---")
    for genre in top_genres:
        subset = genre_df[genre_df['genres'] == genre]
        idx = subset['vote_average'].idxmax()
        top_movie = subset.loc[idx]
        print(f"- {genre}: '{top_movie['title']}' (Rating: {top_movie['vote_average']})")

    # Actor analysis
    actor_df = df.copy()
    actor_df['cast'] = actor_df['cast'].apply(lambda x: get_names(x)[:5])
    actor_df = actor_df.explode('cast')
    top_actors = actor_df['cast'].value_counts().nlargest(5)

    plt.figure(figsize=(8, 5))
    sns.barplot(x=top_actors.values, y=top_actors.index, palette='viridis')
    plt.title('Top 5 Actors with Most Appearances')
    plt.tight_layout()
    plt.savefig('top_5_actors.png')
    print("Chart saved: 'top_5_actors.png'")
    plt.show()

    print("EDA Complete.\n")

# --- Q&A ---

def answer_questions(df):
    print("Step 4: Answering Specific Questions...")
    df['profit'] = df['revenue'] - df['budget']

    def get_movie_details(metric):
        highest_idx = df[metric].idxmax()
        lowest_idx = df[metric].idxmin()
        return df.loc[highest_idx], df.loc[lowest_idx]

    print("\n--- Q1: Movie Records (Highest & Lowest) ---")
    for metric in ['budget', 'revenue', 'profit', 'runtime']:
        h, l = get_movie_details(metric)
        value_h = f"${h[metric]:,}" if metric != 'runtime' else f"{h[metric]} mins"
        value_l = f"${l[metric]:,}" if metric != 'runtime' else f"{l[metric]} mins"
        print(f"Highest {metric.capitalize()}: '{h['title']}' ({value_h})")
        print(f"Lowest {metric.capitalize()}: '{l['title']}' ({value_l})")
        print("-" * 20)

    df['release_year'] = df['release_date'].dt.year
    profitable_movies = df[df['profit'] > 0]
    if not profitable_movies.empty:
        profit_by_year = profitable_movies['release_year'].value_counts()
        most_profitable_year = profit_by_year.idxmax()
        print(f"Year with most profitable movies: {int(most_profitable_year)} ({profit_by_year.max()} movies)")
    else:
        print("No profitable movies in dataset.")

    print("-" * 50)

    # Production companies
    companies_df = df.copy()
    companies_df['production_companies'] = companies_df['production_companies'].apply(get_names)
    companies_df = companies_df.explode('production_companies')
    company_analysis = companies_df.groupby('production_companies').agg(
        total_movies=('title', 'count'),
        total_budget=('budget', 'sum'),
        mean_budget=('budget', 'mean')
    ).sort_values(by='total_movies', ascending=False)
    print("Top Production Companies by Number of Movies:\n", company_analysis.head(5))
    print("-" * 50)

    # Directors
    directors_df = df.copy()
    directors_df['director'] = directors_df['crew'].apply(get_director)
    directors_df.dropna(subset=['director'], inplace=True)
    director_analysis = directors_df.groupby('director').agg(
        total_movies=('title', 'count'),
        total_revenue=('revenue', 'sum')
    ).sort_values(by=['total_movies', 'total_revenue'], ascending=False)
    print("Top Directors by Number of Movies:\n", director_analysis.head(5))
    print("Top Directors by Revenue:\n", director_analysis.sort_values(by='total_revenue', ascending=False).head(5))
    print("-" * 50)

# --- Main ---
if __name__ == '__main__':
    MOVIES_DATA_PATH = os.path.join(os.path.dirname(__file__), 'tmdb_5000_movies.csv')
    CREDITS_DATA_PATH = os.path.join(os.path.dirname(__file__), 'tmdb_5000_credits.csv')

    df = load_and_clean_data(MOVIES_DATA_PATH, CREDITS_DATA_PATH)
    if df is not None:
        exploratory_data_analysis(df.copy())
        answer_questions(df.copy())
        print('\nAnalysis finished successfully!')
