VERSION := 1.0
TAG := opendrill:$(VERSION)

.PHONY: build
build:
	docker build --tag $(TAG) .

.PHONY: run
run:
	docker run --publish 5000:5000 -it $(TAG)
