module.exports = {

    mode: "development",
    entry: "./test",
    devServer: {
        contentBase: './dist'
    },
    module: {
        rules: [
            {
                test: /\.js$/,
                use: ['source-map-loader'],
                enforce: 'pre'
            }
        ]
    }
}