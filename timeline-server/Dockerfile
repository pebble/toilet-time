FROM iojs:1.8.1-slim

# Install git
RUN apt-get update \
  && apt-get install -qy git python build-essential \
  && rm -rf /var/lib/apt/lists/*

# Setup user
RUN useradd -g daemon -m -d /app app
USER app
WORKDIR /app
ENV HOME /app

# Add package info first (allows using cache if deps unchanged)
ADD ./npm-shrinkwrap.json /app/npm-shrinkwrap.json
ADD ./package.json /app/package.json

# Install node modules
RUN npm install

# Add rest of app
ADD . /app

# Expose port 8080 to outside world
EXPOSE 8080

# Set up basic config
ENV PORT 8080

# Default command to run on boot
# ENTRYPOINT []
CMD npm start
